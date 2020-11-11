#include "process_bridge.h"
#include "msg_queue.h"
#include "config.h"
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>

int pb_send_req(void* in, unsigned int insize)
{
    int ret = 0;

    if(!in || !insize) {
        return PB_E_INVALID_PARAMETER;
    }

#ifdef USE_MESSAGE_QUEUE
    ret = req_send_msg_queue(in, insize);
#endif

    return ret;
}

int pb_wait_req(long* type, void** data, unsigned int* size)
{
    int ret = 0;

    if(!type || !data || !size) {
        return PB_E_INVALID_PARAMETER;
    }

    *type = 0;
#ifdef USE_MESSAGE_QUEUE
    ret = req_rcv_msg_queue(type, data, size);
#endif

    return ret;
}

int pb_send_rsp(long type, void* in, unsigned int insize)
{
    int ret = 0;

    if(!in || !insize) {
        return PB_E_INVALID_PARAMETER;
    }

#ifdef USE_MESSAGE_QUEUE
    ret = rsp_send_msg_queue(type, in, insize);
#endif

    return ret;
}

int pb_wait_rsp(long* type, void** data, unsigned int* size)
{
    int ret = 0;

    if(!type || !data || !size) {
        return PB_E_INVALID_PARAMETER;
    }

#ifdef USE_MESSAGE_QUEUE
    ret = rsp_rcv_msg_queue(type, data, size);
#endif

    return ret;
}