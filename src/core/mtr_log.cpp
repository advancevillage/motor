/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

LogClass::LogClass(std::string l_str_fp, std::string l_str_fn)
    :m_str_fp(l_str_fp),m_str_fn(l_str_fn),m_th_out(std::bind(&LogClass::persist,this))
{

}

LogClass::LogClass(const LogClass& g_o_log){
    this->m_str_fn = g_o_log.GetFileName();
    this->m_str_fp = g_o_log.GetFilePath();
}

LogClass::~LogClass() {

}

LogClass& LogClass::operator= (const LogClass& g_o_log){
    this->m_str_fn = g_o_log.GetFileName();
    this->m_str_fp = g_o_log.GetFilePath();
    return (*this);
}

LogClass& LogClass::operator>> (std::string l_str_msg){
    return this->out(l_str_msg);
}

LogClass& LogClass::in(std::string l_str_msg) {
    return (*this);
}

LogClass& LogClass::out(std::string l_str_msg){
    l_str_msg = fmt::format("{}\n", l_str_msg);
    std::fstream fs;
    fs.open(this->m_str_fp + this->m_str_fn, std::fstream::in | std::fstream::out | std::fstream::app);
    fs << l_str_msg;
    fs.close();
    return (*this);
}


LogClass& LogClass::error(std::string l_str_msg){
    std::time_t l_time_temp = std::time(nullptr);
    // Prints "The date is 2016-04-29." (with the current date)
    l_str_msg = fmt::format("{:%Y-%m-%d %H:%M:%S %z} {} {}", *std::localtime(&l_time_temp),"ERROR", l_str_msg);
    return this->out(l_str_msg);
}

LogClass& LogClass::info(std::string l_str_msg){
    std::time_t l_time_temp = std::time(nullptr);
    // Prints "The date is 2016-04-29." (with the current date)
    l_str_msg = fmt::format("{:%Y-%m-%d %H:%M:%S %z} {} {}", *std::localtime(&l_time_temp),"INFO", l_str_msg);
    return this->out(l_str_msg);
}

LogClass& LogClass::debug(std::string l_str_msg){
    std::time_t l_time_temp = std::time(nullptr);
    // Prints "The date is 2016-04-29." (with the current date)
    l_str_msg = fmt::format("{:%Y-%m-%d %H:%M:%S %z} {} {}", *std::localtime(&l_time_temp),"DEBUG", l_str_msg);
    return this->out(l_str_msg);
}

void LogClass::SetFilePath(std::string l_str_fp){
    this->m_str_fp = l_str_fp;
}

std::string LogClass::GetFilePath() const {
    return this->m_str_fp;
}

void LogClass::SetFileName(std::string l_str_fn){
    this->m_str_fn = l_str_fn;
}

std::string LogClass::GetFileName() const {
    return this->m_str_fn;
}

void LogClass::persist(){
    int i = 1;
    while(i < 100){
        std::cout << fmt::format("{0} The thread is {0}", i) << std::endl;
        ++i;
    }
}