/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LOG_INCLUDE_H_
#define _MTR_LOG_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class LogClass {
protected:
    std::string m_str_fp;
    std::string m_str_fn;

private:
    std::thread m_th_out;

public:
    explicit LogClass(std::string l_str_fp = "log/", std::string l_str_fn = "motor.log");
    LogClass(const LogClass& g_o_log);
    virtual ~LogClass();


public:
    LogClass& operator= (const LogClass& g_o_log);
    //LogClass& operator<< (std::string l_str_msg);
    LogClass& operator>> (std::string l_str_msg);
    LogClass& in(std::string l_str_msg);
    LogClass& out(std::string l_str_msg);

    LogClass& error(std::string l_str_msg);
    LogClass& info(std::string l_str_msg);
    LogClass& debug(std::string l_str_msg);

    void SetFileName(std::string l_str_fn);
    std::string GetFileName() const;

    void SetFilePath(std::string l_str_fp);
    std::string GetFilePath() const;

    void persist();
};
#endif
