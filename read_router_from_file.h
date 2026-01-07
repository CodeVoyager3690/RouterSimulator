#ifndef READ_ROUTER_FROM_FILE_H
#define READ_ROUTER_FROM_FILE_H

typedef struct  {
    int nRouters;
    Router** routers; 
} RouterInfo;

RouterInfo* read_routers_from_file(const char* filename);
Router* get_router_by_id(RouterInfo* rinfo, int id);
void free_router_info(RouterInfo* rinfo);

#endif 