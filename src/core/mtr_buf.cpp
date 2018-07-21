/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>

MtrBufferClass::MtrBufferClass(MtrPoolClass *pool, size_t _size)
    :pos(NULL),last(NULL),start(NULL),end(NULL),size(_size),realsize(0)
{
    this->start = pool->MtrAllocPool(_size);
    this->end = this->start + _size;
    this->pos = this->start;
    this->last = this->start;
}

MtrBufferClass::~MtrBufferClass(){
    this->start = NULL;
    this->end = NULL;
    this->pos = NULL;
    this->last = NULL;
    this->size = 0;
    this->realsize = 0;
}

bool MtrBufferClass::MtrBufferIn(void *_src, size_t _size){
    if((this->size - this->realsize) < _size ){
        return false;
    }
    std::memcpy(this->last, _src, _size);
    this->last = this->last + _size;
    this->realsize += _size;
    return true;
}

void MtrBufferClass::MtrBufferReset(){
    std::memset(this->start, 0, this->size);
}