/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>
// partition of pool
MtrPoolPartClass::MtrPoolPartClass(u_char *_start, u_char *_end, mtr_uint_t _status)
    :start(_start),end(_end),status(_status),pre(NULL)
{

}
MtrPoolPartClass::~MtrPoolPartClass(){
    start  = NULL;
    end    = NULL;
    status = 0;
    pre    = NULL;
}

// pool base class
MtrPoolBaseClass::MtrPoolBaseClass(std::string _filedir, std::string _filename)
    :filedir(_filedir),filename(_filename),start(NULL),size(0),max(0),failed(0)
{
    this->size = MTR_PAGESIZE;
    this->Initialize(this->size);
}

MtrPoolBaseClass::MtrPoolBaseClass(size_t _size, std::string _filedir, std::string _filename)
    :filedir(_filedir),filename(_filename),start(NULL),size(_size),max(0),failed(0)
{
    if(this->size & (this->size - 1)){
        size_t temp = 1;
        while(temp < this->size) temp <<= 1;
        this->size = temp;
    }
    this->Initialize(this->size);
}

MtrPoolBaseClass::~MtrPoolBaseClass(){
    delete [] this->start;
    this->start = NULL;
    this->size = 0;
    this->max = 0;
}

void MtrPoolBaseClass::Initialize(size_t _size){
    try{
        this->start = new u_char [_size];
        this->max = _size;
    }catch (std::bad_alloc &ba){
        this->failed++;
        std::fstream fs;
        fs.open(this->filedir + this->filename, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << ba.what();
        fs.close();
    }
}

size_t MtrPoolBaseClass::GetFreeSize() const {
    return this->max;
}

void MtrPoolBaseClass::SetFreeSize(size_t _max){
    this->max = _max;
}

size_t MtrPoolBaseClass::GetSize() const {
    return this->size;
}

std::string MtrPoolBaseClass::GetLogFile() const {
    return this->filedir + this->filename;
}

size_t MtrPoolBaseClass::GetFailed() const {
    return this->failed;
}

// pool data
MtrPoolDataClass::MtrPoolDataClass(std::string _filedir, std::string _filename)
    :MtrPoolBaseClass(_filedir,_filename),last(NULL),end(NULL),next(NULL),tail(NULL)
{
    this->last = this->start;
    this->end = this->start + this->GetSize();
}

MtrPoolDataClass::MtrPoolDataClass(size_t _size, std::string _filedir, std::string _filename)
    :MtrPoolBaseClass(_size,_filedir,_filename),last(NULL),end(NULL),next(NULL),tail(NULL)
{
    this->last = this->start;
    this->end = this->start + this->GetSize();
}

MtrPoolDataClass::~MtrPoolDataClass(){
    while(this->tail){
        MtrPoolPartClass *p = this->tail;
        this->tail = this->tail->pre;
        delete p;
    }
    last = NULL;
    end  = NULL;
    next = NULL;
}

void MtrPoolDataClass::MtrPoolDataRecycle(){
    while(this->tail && this->tail->status == 0){
        MtrPoolPartClass *p = this->tail;
        this->tail = this->tail->pre;
    }
    if(this->tail){
        this->last = this->tail->end;
    }else{
        this->last = this->start;
    }
}
//pool address
MtrPoolAddressClass::MtrPoolAddressClass(MtrPoolDataClass *_pool, u_char *_addr)
    :pool(_pool),addr(_addr)
{

}
MtrPoolAddressClass::MtrPoolAddressClass(const MtrPoolAddressClass &_pooladdr){
    this->pool = _pooladdr.pool;
    this->addr = _pooladdr.addr;
}
MtrPoolAddressClass::MtrPoolAddressClass(MtrPoolAddressClass* &_pooladdr){
    this->pool = _pooladdr->pool;
    this->addr = _pooladdr->addr;
}
MtrPoolAddressClass::~MtrPoolAddressClass(){
    this->pool = NULL;
    this->addr = NULL;
}
void MtrPoolAddressClass::operator=(MtrPoolAddressClass &_pooladdr){
    this->pool = _pooladdr.pool;
    this->addr = _pooladdr.addr;
}
//pool
MtrPoolClass::MtrPoolClass(LogProcessor *_log, size_t _max)
    :log(_log),small(NULL),large(NULL),smallen(0),largelen(0),max(_max)
{
    this->small = new MtrPoolDataClass(_max, _log->GetLogDir(),_log->GetErrLogFileName());
    smallen++;
}

MtrPoolClass::~MtrPoolClass(){
    while(small){
        MtrPoolDataClass    *p;
        p = small;
        small = small->next;
        delete p;
    }
    while(large){
        MtrPoolDataClass    *p;
        p = large;
        large = large->next;
        delete p;
    }
    smallen = 0;
    largelen = 0;
}

void MtrPoolClass::MtrAllocPool(MtrPoolAddressClass& pa, size_t _size){
    if(this->max >= _size){
        return this->MtrAllocSmallPool(pa, _size);
    }
    return this->MtrAllocLargePool(pa, _size);
}

void MtrPoolClass::MtrAllocSmallPool(MtrPoolAddressClass& pa, size_t _size){
    u_char  *m = NULL;
    MtrPoolDataClass    *p = this->small;
    while(p && p->last){
        m = p->last;
        size_t free = p->GetFreeSize();
        if(free >= _size){
            MtrPoolPartClass *poolpart = new MtrPoolPartClass();
            poolpart->start = p->last;
            p->last = m + _size;
            poolpart->end = p->last;
            p->SetFreeSize(free - _size);
            if(NULL == p->tail){
                p->tail = poolpart;
            }else{
                poolpart->pre = p->tail;
                p->tail = poolpart;
            }
            pa.pool = p;
            pa.addr = m;
        }
        p = p->next;
    }
    this->MtrAllocblock(pa,_size,0);
}

void MtrPoolClass::MtrAllocblock(MtrPoolAddressClass& pa, size_t _size, size_t type){
    u_char  *m = NULL;
    size_t  block = type ? _size : this->max;
    MtrPoolDataClass  *p = new MtrPoolDataClass(block, this->log->GetLogDir(),this->log->GetErrLogFileName());
    if(p->last) {
        MtrPoolPartClass *poolpart = new MtrPoolPartClass();
        poolpart->start = p->last;
        m = p->last;
        p->last = p->last + _size;
        poolpart->end = p->last;
        p->SetFreeSize(p->GetFreeSize() - _size);
        if(NULL == p->tail){
            p->tail = poolpart;
        }else{
            poolpart->pre = p->tail;
            p->tail = poolpart;
        }
        MtrPoolDataClass    *q = type ? this->large : this->small;
        while(q->next) q = q->next;
        q->next = p;
        this->smallen = type ? this->smallen : (++this->smallen);
        this->largelen = type ? (++this->largelen) : this->largelen;
        pa.pool = p;
        pa.addr = m;
    }
}

void MtrPoolClass::MtrAllocLargePool(MtrPoolAddressClass& pa, size_t _size){
    u_char  *m = NULL;
    if(this->large == NULL){
        this->large = new MtrPoolDataClass(_size, this->log->GetLogDir(),this->log->GetErrLogFileName());
        if(this->large->last){
            m = this->large->last;
            this->large->last = this->large->last + _size;
            this->large->SetFreeSize(this->large->GetFreeSize() - _size);
            this->largelen++;
        }else{
            this->large = NULL;
        }
        pa.pool = this->large;
        pa.addr = m;
    } else {
        this->MtrAllocblock(pa,_size, 1);
    }  
}

size_t MtrPoolClass::GetMaxSize() const {
    return this->max;
}

size_t MtrPoolClass::GetSmallPoolListLength() const {
    return this->smallen;
}

size_t MtrPoolClass::GetLargePoolListLength() const {
    return this->largelen;
}

//container base class
MtrContainerBaseClass::MtrContainerBaseClass(MtrPoolClass *pool, size_t _size)
    :pa(),start(NULL),end(NULL),size(_size)
{
    pool->MtrAllocPool(this->pa, _size);
    this->start = this->pa.addr;
    this->end   = this->start + _size;
}
MtrContainerBaseClass::~MtrContainerBaseClass(){
    MtrPoolPartClass *pp = this->pa.pool->tail;
    while(pp){
        if(pp->start == this->start){
            pp->status = 0;
            std::memset(this->start, 0, this->size);
            this->pa.pool->MtrPoolDataRecycle();
            break;
        }
        pp = pp->pre;
    }
    this->start = NULL;
    this->end   = NULL;
    this->size  = 0;
}