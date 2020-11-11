#include "msg_queue.h"
#include "process_bridge.h"
#include "config.h"

#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>

#ifdef USE_MESSAGE_QUEUE

#define MAX_MSG_SIZE 1048576
#define MSG_QUEUE_DIR "/"
#define MSG_QUEUE_CLIENT_ID 0
#define MSG_QUEUE_SERVER_ID 255
#define MSG_QUEUE_PERMISSION 0666

struct msgbuf {
    long mtype;
    unsigned char mtext[0];
};

static int msg_queue_send(int msgid, long type, void* data, unsigned int size)
{
    struct msgbuf* msg = NULL;
    int ret = 0;

    msg = calloc(1, sizeof(struct msgbuf) + size);
    if(!msg) {
        return PB_E_OUT_OF_MEMORY;
    }

    msg->mtype = type;
    memcpy(msg->mtext, data, size);

    ret = msgsnd(msgid, msg, size, 0);
    if(-1 == ret) {
        ret = PB_E_KERNEL;
    }

    free(msg);
    return ret;
}

static int msg_queue_rcv(int msgid, long* type, void** data, unsigned int* size)
{
    struct msgbuf* msg = NULL;
    int ret = 0;

    msg = calloc(1, MAX_MSG_SIZE);
    if(!msg) {
        return PB_E_OUT_OF_MEMORY;
    }

    ret = msgrcv(msgid, msg, MAX_MSG_SIZE, *type, 0);
    if(-1 == ret) {
        ret = PB_E_KERNEL;
        goto exit;
    }

    *type = msg->mtype;
    *size = (unsigned int)ret;
    if(*size) {
        *data = calloc(1, *size);
        if(!(*data)) {
            ret = PB_E_OUT_OF_MEMORY;
            goto exit;
        }

        memcpy(*data, msg->mtext, *size);
    }

    ret = 0;

exit:
    free(msg);
    return ret;
}

int req_send_msg_queue(void* data, unsigned int size)
{
    key_t key;
    int msgid = 0;

    key = ftok(MSG_QUEUE_DIR, MSG_QUEUE_CLIENT_ID);
    if(-1 == key) {
        return PB_E_KERNEL;
    }

    msgid = msgget(key, IPC_CREAT | MSG_QUEUE_PERMISSION);
    if(-1 == msgid) {
        return PB_E_KERNEL;
    }

    return msg_queue_send(msgid, pthread_self(), data, size);
}

int req_rcv_msg_queue(long* type, void** data, unsigned int* size)
{
    key_t key;
    int msgid = 0;

    key = ftok(MSG_QUEUE_DIR, MSG_QUEUE_CLIENT_ID);
    if(-1 == key) {
        return PB_E_KERNEL;
    }

    msgid = msgget(key, IPC_CREAT | MSG_QUEUE_PERMISSION);
    if(-1 == msgid) {
        return PB_E_KERNEL;
    }

    return msg_queue_rcv(msgid, type, data, size);
}

int rsp_send_msg_queue(long type, void* data, unsigned int size)
{
    key_t key;
    int msgid = 0;

    key = ftok(MSG_QUEUE_DIR, MSG_QUEUE_SERVER_ID);
    if(-1 == key) {
        return PB_E_KERNEL;
    }

    msgid = msgget(key, IPC_CREAT | MSG_QUEUE_PERMISSION);
    if(-1 == msgid) {
        return PB_E_KERNEL;
    }

    return msg_queue_send(msgid, type, data, size);
}

int rsp_rcv_msg_queue(long* type, void** data, unsigned int* size)
{
    key_t key;
    int msgid = 0;

    key = ftok(MSG_QUEUE_DIR, MSG_QUEUE_SERVER_ID);
    if(-1 == key) {
        return PB_E_KERNEL;
    }

    msgid = msgget(key, IPC_CREAT | MSG_QUEUE_PERMISSION);
    if(-1 == msgid) {
        return PB_E_KERNEL;
    }

    return msg_queue_rcv(msgid, type, data, size);
}

#endif /* USE_MESSAGE_QUEUE */