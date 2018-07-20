/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_MEM_INCLUDE_H_
#define _MTR_MEM_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

/**
 *@brief: memory pool data
 */ 
class MtrPoolDataClass {
public:
    u_char  *last;
    u_char  *start;
    u_char  *end;

public:
    MtrPoolDataClass    *next;

protected:
    size_t  max;
    std::string filedir;
    std::string filename;

public:
    explicit MtrPoolDataClass(std::string _filedir);
    explicit MtrPoolDataClass(std::string _filedir, size_t _poolsize);
    ~MtrPoolDataClass();

private:
    void Initialize(size_t _poolsize);
};

#endif