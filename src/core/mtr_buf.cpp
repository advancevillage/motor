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

bool MtrBufferClass::in(void *_src, size_t _size){
    if((this->size - this->realsize) < _size ){
        return false;
    }
    std::memcpy(this->last, _src, _size);
    this->last = this->last + _size;
    this->realsize += _size;
    return true;
}

bool MtrBufferClass::in(const void *_src, size_t _size){
    if((this->size - this->realsize) < _size ){
        return false;
    }
    std::memcpy(this->last, _src, _size);
    this->last = this->last + _size;
    this->realsize += _size;
    return true;
}

bool MtrBufferClass::in(std::string _str){
    return this->in(_str.data(), _str.length());
}

bool MtrBufferClass::operator<<(std::string _str){
    return this->in(_str.data(), _str.length());
}

bool MtrBufferClass::out(std::string file){
    std::ofstream fs;
    fs.open(file, std::ofstream::out | std::ofstream::app);
    fs.write((char*)this->pos,this->realsize);
    fs.close();
    return true;
}

bool MtrBufferClass::operator>> (std::string file){
    return this->out(file);
}

void MtrBufferClass::reset(){
    std::memset(this->pos, 0, this->realsize);
    this->last = this->pos;
    this->realsize = 0;
}