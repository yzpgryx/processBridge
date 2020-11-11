#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

typedef struct pb_req_st pbreq_t;
typedef struct pb_rsp_st pbrsp_t;

struct pb_req_st {
    int cid;
    unsigned int data_size;
    unsigned char data[0];
};

struct pb_rsp_st {
    int ret;
    unsigned int data_size;
    unsigned char data[0];
};

#endif