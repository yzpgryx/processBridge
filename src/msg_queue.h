#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#ifdef USE_MESSAGE_QUEUE

int req_send_msg_queue(void* data, unsigned int size);
int req_rcv_msg_queue(long* type, void** data, unsigned int* size);
int rsp_send_msg_queue(long type, void* data, unsigned int size);
int rsp_rcv_msg_queue(long* type, void** data, unsigned int* size);

#endif /* USE_MESSAGE_QUEUE */

#ifdef __cplusplus
extern }
#endif

#endif