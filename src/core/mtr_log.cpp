/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>
LogProcessor::LogProcessor(MtrLogLevelEnum _level, std::string _filedir, std::string _errlog, std::string _mtrlog)
    :level(_level),filedir(_filedir),errlog(_errlog),mtrlog(_mtrlog)
{

}

LogProcessor::~LogProcessor()
{
}

MtrLogLevelEnum LogProcessor::GetLogLevel() const {
    return this->level;
}

void LogProcessor::SetLogLevel(MtrLogLevelEnum _level){
    this->level = _level;
}

std::string LogProcessor::GetErrLogFileName() const {
    return this->errlog;
}

std::string LogProcessor::GetMtrLogFileName() const {
    return this->mtrlog;
}

std::string LogProcessor::GetLogDir() const {
    return this->filedir;
}