/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>
#include <motor.h>

int main(){
    size_t max = MTR_PAGESIZE;
    std::string l_str_fp = "log/";
    std::string l_str_fn = "error.log";
    PoolClass* g_po_p = new PoolClass(l_str_fp,l_str_fn);
    LogClass g_o_log;
    int i = 0;
    while(true){
        i = 1;
    }
    return MTR_OK;
}
