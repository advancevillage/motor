/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>

MtrBufferClass::MtrBufferClass(MtrPoolClass *pool, size_t _size)
    :MtrContainerBaseClass(pool, _size), pos(NULL),last(NULL),realsize(0)
{
    this->pos = this->start;
    this->last = this->start;
}

MtrBufferClass::~MtrBufferClass(){
    this->pos = NULL;
    this->last = NULL;
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

bool MtrBufferClass::MtrBufferIn(const void *_src, size_t _size){
    if((this->size - this->realsize) < _size ){
        return false;
    }
    std::memcpy(this->last, _src, _size);
    this->last = this->last + _size;
    this->realsize += _size;
    return true;
}