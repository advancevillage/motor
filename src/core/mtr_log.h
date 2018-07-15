/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LOG_INCLUDE_H_
#define _MTR_LOG_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class MtrLogPoolDataBlock {
public:
    u_char              *start;
    u_char              *last;
    u_char              *end;
    MtrLogPoolDataBlock *next;
protected:
    size_t              max;
    std::string         errlog;
    mtr_uint_t          failed;

public:
    explicit MtrLogPoolDataBlock();
    explicit MtrLogPoolDataBlock(std::string _errlog);
    explicit MtrLogPoolDataBlock(size_t _mem, std::string _errlog);
    ~MtrLogPoolDataBlock(); 

private:
    void Initialize(size_t _mem);
};

#endif
