/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>

MtrPoolDataClass::MtrPoolDataClass(std::string _filedir)
    :start(NULL),last(NULL),end(NULL),next(NULL),max(0),filedir(_filedir),filename("error.log")
{
    size_t pagesize = MTR_PAGESIZE;
    this->Initialize(pagesize);
}

MtrPoolDataClass::MtrPoolDataClass(std::string _filedir, size_t _pagesize)
    :start(NULL),last(NULL),end(NULL),next(NULL),max(0),filedir(_filedir),filename("error.log")
{
    if(_pagesize & (_pagesize -1)){
        size_t temp = 1;
        while(temp < _pagesize) temp <<= 1;
        _pagesize = temp;
    }
    this->Initialize(_pagesize);
}

MtrPoolDataClass::~MtrPoolDataClass(){
    delete [] start;
    start = NULL;
    last = NULL;
    end = NULL;
    next = NULL;
    max = 0;
}


void MtrPoolDataClass::Initialize(size_t _poolsize){
    try{
        start = new u_char [_poolsize];
        last = start;
        end = start + _poolsize;
        max = end - last;
    }catch (std::bad_alloc &ba){
        std::fstream fs;
        fs.open(this->filedir + this->filename, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << ba.what();
        fs.close();
    }
}