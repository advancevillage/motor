/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LOG_INCLUDE_H_
#define _MTR_LOG_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class MtrLogPoolClass {
public:
    u_char              *start;
    u_char              *last;
    u_char              *end;
    MtrLogPoolClass     *next;
protected:
    size_t              max;
    std::string         errlog;
    mtr_uint_t          failed;

public:
    explicit MtrLogPoolClass();
    explicit MtrLogPoolClass(std::string _errlog);
    explicit MtrLogPoolClass(size_t _mem, std::string _errlog);
    ~MtrLogPoolClass(); 

private:
    void Initialize(size_t _mem);
};

#endif
