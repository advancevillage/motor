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
    MtrBufferClass buf(pool, 1024);
    std::string  file = "log/motor.log";
    std::time_t t = std::time(nullptr);
    // Prints "The date is 2016-04-29." (with the current date)
    std::string  str = fmt::format("[{:%Y-%m-%d %H:%M:%S %z}] {} love {}\n", *std::localtime(&t), "richard", "kelly");
    buf << str;
    buf >> file;
    buf.reset();
    return MTR_OK;
}
