#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "process_bridge.h"

int main(int argc, const char** argv)
{
    int ret = 0;
    unsigned char* data = NULL;
    unsigned int data_size = 0;
    pthread_t req_tid = 0;
    char rsp[] = {"this is a response msg"};

    while(1) {
        printf("wait a request from client:\n");
        ret = pb_wait_req((long*)&req_tid, (void**)&data, &data_size);
        if(ret) {
            printf("    wait request fialed : %d\n", ret);
        } else {
            printf("    got a request : tid : %ld\n", req_tid);
            printf("    %s\n", (char*)data);
        }

        free(data);
        data = NULL;
        data_size = 0;

        ret = pb_send_rsp(req_tid, rsp, sizeof(rsp));
        if(ret) {
            printf("send a response to client failed : %d\n", ret);
        } else {
            printf("send response success.\n");
        }
    }
}