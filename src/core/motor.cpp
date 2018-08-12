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
    return MTR_OK;
}
