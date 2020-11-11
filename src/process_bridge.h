#ifndef __PROCESS_BRIDGE_H__
#define __PROCESS_BRIDGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PB_E_INVALID_PARAMETER  -1
#define PB_E_OUT_OF_MEMORY      -2
#define PB_E_KERNEL             -3

int pb_send_req(void* in, unsigned int insize);
int pb_wait_req(long* type, void** data, unsigned int* size);

int pb_send_rsp(long type, void* in, unsigned int insize);
int pb_wait_rsp(long* type, void** data, unsigned int* size);

#ifdef __cplusplus
extern }
#endif

#endif