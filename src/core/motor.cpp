/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>
#include <motor.h>

int main(){
    LogProcessor *log = new LogProcessor();
    size_t max = MTR_PAGESIZE;
    MtrPoolClass *pool = new MtrPoolClass(log, max);
    char kelly[1024] = "kelly, I love you forever!";
    char richard[2048] = "richard, I am a ...";
    MtrBufferClass *buf = new MtrBufferClass(pool, 3*1024);
    buf->MtrBufferIn(kelly, sizeof(kelly));
    buf->MtrBufferIn(richard, sizeof(richard));
    fmt::print("Richard: {}\n", std::string(kelly));
    return MTR_OK;
}
