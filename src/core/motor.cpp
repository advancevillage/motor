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
    char kelly[] = "kelly, I love you forever!";
    char richard[] = "richard, I am a ...";
    MtrBufferClass *buf = new MtrBufferClass(pool, 1024);
    MtrBufferClass *buf01 = new MtrBufferClass(pool, 2*1024);
    MtrBufferClass *buf02 = new MtrBufferClass(pool, 5*1024);
    std::string test = "你是我的最爱";
    std::string test02 = fmt::format("{} love {}", "richard", "kelly");
    buf->MtrBufferIn(kelly, std::strlen(kelly));
    buf->MtrBufferIn(richard, std::strlen(richard));
    buf->MtrBufferIn(test.data(), test.length());
    buf->MtrBufferIn(test02.data(), test02.length());
    fmt::print("Richard: {}\n", std::string(kelly));
    return MTR_OK;
}
