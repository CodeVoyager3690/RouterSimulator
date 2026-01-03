#ifndef READ_ROUTER_FROM_FILE_H
#define READ_ROUTER_FROM_FILE_H

typedef struct  {
    int nRouters;
    Router** routers; 
} RouterInfo;

RouterInfo* read_routers_from_file(const char* filename);

#endif 