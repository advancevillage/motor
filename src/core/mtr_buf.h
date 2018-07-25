/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_BUF_INCLUDE_H_
#define _MTR_BUF_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class MtrBufferClass : public MtrContainerBaseClass {
public:
    u_char      *pos;
    u_char      *last;
    u_char      *end;

protected:
    size_t      realsize;

public:
    explicit MtrBufferClass(MtrPoolClass *pool, size_t _size);
    ~MtrBufferClass();
    
public:
    bool MtrBufferIn(void *_src, size_t _size);
    bool MtrBufferIn(const void *_src, size_t _size);
};
#endif