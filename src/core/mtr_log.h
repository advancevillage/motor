/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LOG_INCLUDE_H_
#define _MTR_LOG_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

typedef enum {
    MTR_LOG_STDERR = 0,
    MTR_LOG_EMERG  = 1,
    MTR_LOG_ALERT  = 2,
    MTR_LOG_CRIT   = 3,
    MTR_LOG_ERR    = 4,
    MTR_LOG_WARN   = 5,
    MTR_LOG_NOTICE = 6,
    MTR_LOG_INFO   = 7,
    MTR_LOG_DEBUG  = 8
}MtrLogLevelEnum;

class LogProcessor {
protected:
    MtrLogLevelEnum  level;
    std::string filedir;
    std::string errlog;
    std::string mtrlog;

public:
    explicit LogProcessor(MtrLogLevelEnum _level = MtrLogLevelEnum::MTR_LOG_INFO, std::string _filedir = "log/", std::string _errlog = "error.log", std::string _mtrlog = "motor.log");
    ~LogProcessor();
public:
    MtrLogLevelEnum GetLogLevel() const;
    void SetLogLevel(MtrLogLevelEnum _level = MtrLogLevelEnum::MTR_LOG_INFO);
    std::string GetLogDir() const;
    std::string GetErrLogFileName() const;
    std::string GetMtrLogFileName() const;
};

#endif
