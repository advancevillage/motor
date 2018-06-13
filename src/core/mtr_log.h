/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LOG_INCLUDE_H_
#define _MTR_LOG_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class LogProcessor{
protected:
    std::string file;
    int         level;

private:
    auto        sink;
    auto        loger;   

public:
    LogProcessor();
    ~LogProcessor();

public:
    string GetLogFileName();
};

#endif
