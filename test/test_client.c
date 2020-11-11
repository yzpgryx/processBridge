#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "process_bridge.h"

int main(int argc, const char** argv)
{
    int ret = 0;
    char msg[] = {"this is a client message"};
    unsigned char* rsp = NULL;
    unsigned int rsp_size = 0;
    long type = (long)pthread_self();

    while(1) {
        printf("send a message to server, press \"enter\"\n");
        while('\n' != getchar());
        
        ret = pb_send_req(msg, sizeof(msg));
        if(ret) {
            printf("send msg failed : %d\n", ret);
        } else {
            printf("send msg success, tid : %ld!\n", pthread_self());
        }

        ret = pb_wait_rsp(&type, (void**)&rsp, &rsp_size);
        if(ret) {
            printf("wait response failed : %d\n", ret);
        } else {
            printf("got response : %s\n", rsp);
        }
    }
}