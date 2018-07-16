/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

MtrLogPoolDataBlock::MtrLogPoolDataBlock()
    :start(NULL),last(NULL),end(NULL),next(NULL),failed(0),max(0),errlog("log/error.log") 
{
    size_t pagesize = MTR_PAGESIZE;
    this->Initialize(pagesize);
}

MtrLogPoolDataBlock::MtrLogPoolDataBlock(std::string _errlog)
    :start(NULL),last(NULL),end(NULL),next(NULL),failed(0),max(0),errlog(_errlog)
{
    size_t pagesize = MTR_PAGESIZE;
    this->Initialize(pagesize);
}

MtrLogPoolDataBlock::MtrLogPoolDataBlock(size_t _mem, std::string _errlog)
    :start(NULL),last(NULL),end(NULL),next(NULL),failed(0),max(0),errlog(_errlog)
{
    if(_mem & (_mem -1)){
        size_t temp = 1;
        while(temp < _mem) temp <<= 1;
        _mem = temp;
    }
    this->Initialize(_mem);
}

void MtrLogPoolDataBlock::Initialize(size_t _mem){
    try{
        start = new u_char [_mem];
        last = start;
        end = start + _mem;
        max = end - last;
        failed = 0;
    }catch (std::bad_alloc &ba){
        failed += 1;
        std::fstream fs;
        fs.open(this->errlog, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << ba.what();
        fs.close();
    }
}

MtrLogPoolDataBlock::~MtrLogPoolDataBlock(){
    delete [] start;
    start = NULL;
    end = NULL;
    last = NULL;
    next = NULL;
    max = 0;
    failed = 0;
}