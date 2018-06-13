/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

LogProcessor::LogProcessor(){
    sink = std::make_shared<spdlog::sinks::daily_file_sink<std::mutex,spdlog::sinks::dateonly_daily_file_name_calculator>>("motor.log", 23, 59);
}

LogProcessor::~LogProcessor(){

}