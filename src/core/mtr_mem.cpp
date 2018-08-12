/*
 * Copyright (C) Richard Sun
 */
//PoolBaseClass
#include <mtr_config.h>
#include <mtr_core.h>

PoolBaseClass::PoolBaseClass(std::string l_str_fp, std::string l_str_fn)
    :m_puch_start(NULL),m_puch_end(NULL),m_n_capacity(0),m_n_size(0),m_str_filepath(l_str_fp),m_str_filename(l_str_fn)
{
    this->m_n_capacity = MTR_PAGESIZE;
    this->init(this->m_n_capacity);
}

PoolBaseClass::PoolBaseClass(size_t l_n_size, std::string l_str_fp, std::string l_str_fn)
    :m_puch_start(NULL),m_n_capacity(0),m_n_size(0),m_str_filepath(l_str_fp),m_str_filename(l_str_fn)
{
    size_t l_n_temp = l_n_size;
    if(l_n_size & (l_n_size -1)){
        l_n_temp = 1;
        while(l_n_temp < l_n_size) l_n_temp <<= 1;
    }
    this->m_n_capacity = l_n_temp;
    this->init(this->m_n_capacity);
}

PoolBaseClass::PoolBaseClass(const PoolBaseClass& g_o_pb){
    this->m_n_capacity = g_o_pb.capacity();
    this->m_n_size = g_o_pb.getsize();
    this->m_str_filename = g_o_pb.GetFileName();
    this->m_str_filepath = g_o_pb.GetFilePath();
    this->m_puch_start = NULL;
    this->init(this->m_n_capacity);
    memcpy(this->m_puch_start,g_o_pb.m_puch_start,g_o_pb.capacity());
}

PoolBaseClass::~PoolBaseClass(){
    delete [] this->m_puch_start;
    this->m_n_capacity = 0;
    this->m_n_size = 0;
}

PoolBaseClass& PoolBaseClass::operator= (const PoolBaseClass& g_o_pb){
    this->m_n_capacity = g_o_pb.capacity();
    this->m_n_size = g_o_pb.getsize();
    this->m_str_filename = g_o_pb.GetFileName();
    this->m_str_filepath = g_o_pb.GetFilePath();
    this->m_puch_start = NULL;
    this->init(this->m_n_capacity);
    memcpy(this->m_puch_start,g_o_pb.m_puch_start,g_o_pb.capacity());
    return (*this);   
}

void PoolBaseClass::init(size_t l_n_size){
    try{
        this->m_puch_start = new u_char[l_n_size];
        this->m_puch_end = this->m_puch_start + l_n_size;
    }catch (std::bad_alloc &ba){
        std::fstream fs;
        fs.open(this->m_str_filepath + this->m_str_filename, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << ba.what();
        fs.close();
    }
}

size_t PoolBaseClass::getsize() const {
    return this->m_n_size;
}

void PoolBaseClass::setsize(size_t l_n_size){
    this->m_n_size = l_n_size;
}

size_t PoolBaseClass::capacity() const {
    return this->m_n_capacity;
}

std::string PoolBaseClass::GetFilePath() const {
    return this->m_str_filepath;
}

std::string PoolBaseClass::GetFileName() const {
    return this->m_str_filename;
}

//PoolPartClass
PoolPartClass::PoolPartClass()
    :m_puch_start(NULL),m_puch_end(NULL),m_po_pp_pre(NULL),m_n_status(1)
{

}

PoolPartClass::PoolPartClass(const PoolPartClass& g_o_pp){
    this->m_puch_start = g_o_pp.m_puch_start;
    this->m_puch_end = g_o_pp.m_puch_end;
    this->m_po_pp_pre = g_o_pp.m_po_pp_pre;
    this->m_n_status = g_o_pp.m_n_status;
}

PoolPartClass::~PoolPartClass(){
    this->m_puch_start = NULL;
    this->m_puch_end = NULL;
    this->m_po_pp_pre = NULL;
    this->m_n_status = 0;
}

PoolPartClass& PoolPartClass::operator= (const PoolPartClass& g_o_pp){
    this->m_puch_start = g_o_pp.m_puch_start;
    this->m_puch_end = g_o_pp.m_puch_end;
    this->m_po_pp_pre = g_o_pp.m_po_pp_pre;
    this->m_n_status = g_o_pp.m_n_status;
    return (*this);
}

//PoolDataClass
PoolDataClass::PoolDataClass(std::string l_str_fp, std::string l_str_fn)
    :PoolBaseClass(l_str_fp,l_str_fn),m_puch_last(NULL),m_po_pp_tail(NULL),m_po_pd_next(NULL)
{
    this->m_puch_last = this->m_puch_start;
}

PoolDataClass::PoolDataClass(size_t l_n_size, std::string l_str_fp, std::string l_str_fn)
    :PoolBaseClass(l_n_size, l_str_fp,l_str_fn),m_puch_last(NULL),m_po_pp_tail(NULL),m_po_pd_next(NULL)
{
    this->m_puch_last = this->m_puch_start;
}

PoolDataClass::PoolDataClass(const PoolDataClass& g_o_pd) : PoolBaseClass(g_o_pd) {
    this->m_puch_last = g_o_pd.m_puch_last;
    this->m_po_pd_next = g_o_pd.m_po_pd_next;
    this->m_po_pp_tail = g_o_pd.m_po_pp_tail;
}

PoolDataClass::~PoolDataClass() {
    while(this->m_po_pp_tail){
        PoolPartClass* m_po_pp_temp = this->m_po_pp_tail;
        this->m_po_pp_tail = this->m_po_pp_tail->m_po_pp_pre;
        delete m_po_pp_temp;
    }
    this->m_puch_last = NULL;
    this->m_po_pd_next = NULL;
    this->m_po_pp_tail = NULL;
}

PoolDataClass& PoolDataClass::operator=(const PoolDataClass& g_o_pd){
    if(this == &g_o_pd) return (*this);
    static_cast<PoolBaseClass&>(*this) = g_o_pd;
    this->m_puch_last = g_o_pd.m_puch_last;
    this->m_po_pd_next = g_o_pd.m_po_pd_next;
    this->m_po_pp_tail = g_o_pd.m_po_pp_tail;
    return (*this);
}

void PoolDataClass::recycle() {
    while(this->m_po_pp_tail && this->m_po_pp_tail->m_n_status == 0){
        PoolPartClass* m_po_pp_temp = this->m_po_pp_tail;
        this->m_po_pp_tail = this->m_po_pp_tail->m_po_pp_pre;
        delete m_po_pp_temp;
    }
    if(this->m_po_pp_tail){
        this->m_puch_last = this->m_po_pp_tail->m_puch_end;
    }else{
        this->m_puch_last = this->m_puch_start;
    }
}

size_t PoolDataClass::GetPartCount() const {
    size_t l_n_count = 0;
    PoolPartClass* l_po_pp_temp = this->m_po_pp_tail;
    while(l_po_pp_temp){
        ++l_n_count;
        l_po_pp_temp = l_po_pp_temp->m_po_pp_pre;
    }
    return l_n_count;
}

//PoolRetClass
PoolRetClass::PoolRetClass(PoolDataClass* l_po_pd_alloc, u_char* l_puch_addr)
    :m_po_pd_alloc(l_po_pd_alloc),m_puch_addr(l_puch_addr)
{

}

PoolRetClass::PoolRetClass(const PoolRetClass& g_o_pr){
    this->m_po_pd_alloc = g_o_pr.m_po_pd_alloc;
    this->m_puch_addr = g_o_pr.m_puch_addr;
}

PoolRetClass::~PoolRetClass(){
    this->m_po_pd_alloc = NULL;
    this->m_puch_addr = NULL;
}

PoolRetClass& PoolRetClass::operator= (const PoolRetClass& g_o_pr){
    this->m_po_pd_alloc = g_o_pr.m_po_pd_alloc;
    this->m_puch_addr = g_o_pr.m_puch_addr;
}

//PoolClass
PoolClass::PoolClass(std::string l_str_fp, std::string l_str_fn)
    :m_po_pd_small(NULL),m_po_pd_large(NULL),m_n_small_len(0),m_n_large_len(0),m_n_max(0)
{
    this->m_n_max = MTR_PAGESIZE;
    this->m_po_pd_small = new PoolDataClass(this->m_n_max, l_str_fp, l_str_fn);
    this->m_n_small_len++;
}

PoolClass::PoolClass(size_t l_n_max, std::string l_str_fp, std::string l_str_fn)
    :m_po_pd_small(NULL),m_po_pd_large(NULL),m_n_small_len(0),m_n_large_len(0),m_n_max(0)
{
    this->m_n_max = MTR_PAGESIZE;
    this->m_n_max = l_n_max > this->m_n_max ? l_n_max : this->m_n_max;
    this->m_po_pd_small = new PoolDataClass(this->m_n_max, l_str_fp, l_str_fn);
    this->m_n_small_len++;
}

PoolClass::PoolClass(const PoolClass& g_o_p){
    this->m_po_pd_small = g_o_p.m_po_pd_small;
    this->m_po_pd_large = g_o_p.m_po_pd_large;
    this->m_n_large_len = g_o_p.GetLargePoolLength();
    this->m_n_small_len = g_o_p.GetSmallPoolLength();
    this->m_n_max = g_o_p.max();
}

PoolClass::~PoolClass() {
    while(this->m_po_pd_small){
        PoolDataClass* l_po_pd_temp = this->m_po_pd_small;
        this->m_po_pd_small = this->m_po_pd_small->m_po_pd_next;
        delete l_po_pd_temp;
    }
    while(this->m_po_pd_large){
        PoolDataClass* l_po_pd_temp = this->m_po_pd_large;
        this->m_po_pd_large = this->m_po_pd_large->m_po_pd_next;
        delete l_po_pd_temp;
    }
    this->m_n_small_len = 0;
    this->m_n_large_len = 0;
}

PoolClass& PoolClass::operator= (const PoolClass& g_o_p){
    this->m_po_pd_small = g_o_p.m_po_pd_small;
    this->m_po_pd_large = g_o_p.m_po_pd_large;
    this->m_n_large_len = g_o_p.GetLargePoolLength();
    this->m_n_small_len = g_o_p.GetSmallPoolLength();
    this->m_n_max = g_o_p.max();
    return (*this);
}

size_t PoolClass::GetSmallPoolLength() const {
    return this->m_n_small_len;
}

size_t PoolClass::GetLargePoolLength() const {
    return this->m_n_large_len;
}

size_t PoolClass::max() const {
    return this->m_n_max;
}

void PoolClass::alloc(PoolRetClass& g_o_pr, size_t l_n_size){
    if(l_n_size > this->m_n_max){
        this->AllocSmall(g_o_pr, l_n_size);
    }
    this->AllocLarge(g_o_pr,l_n_size);
}

void PoolClass::AllocSmall(PoolRetClass& g_o_pr, size_t l_n_size){
    u_char* l_puch_addr = NULL;
    PoolDataClass* l_po_pd_temp = this->m_po_pd_small;
    while(l_po_pd_temp && l_po_pd_temp->m_puch_last ){
        l_puch_addr = l_po_pd_temp->m_puch_last;
        size_t l_n_freesize = l_po_pd_temp->capacity() - l_po_pd_temp->getsize();
        if(l_n_size <= l_n_freesize){
            PoolPartClass* l_po_pp = new PoolPartClass();
            l_po_pp->m_puch_start = l_po_pd_temp->m_puch_last;
            l_po_pd_temp->m_puch_last += l_n_size;
            l_po_pp->m_puch_end = l_po_pd_temp->m_puch_last;
            l_po_pd_temp->setsize(l_po_pd_temp->getsize()+l_n_size);
            if(l_po_pd_temp->m_po_pp_tail){
                l_po_pd_temp->m_po_pp_tail = l_po_pp;
            }else{
                l_po_pp->m_po_pp_pre = l_po_pd_temp->m_po_pp_tail;
                l_po_pd_temp->m_po_pp_tail = l_po_pp;
            }
            g_o_pr.m_po_pd_alloc = l_po_pd_temp;
            g_o_pr.m_puch_addr = l_puch_addr;
            break;
        }
        l_po_pd_temp = l_po_pd_temp->m_po_pd_next;
    }
    if(!l_po_pd_temp) this->Allocblock(g_o_pr, l_n_size, 0);
}

void PoolClass::Allocblock(PoolRetClass& g_o_pr, size_t l_n_size, size_t l_n_type) {
    u_char* l_puch_addr = NULL;
    size_t l_n_block = l_n_type ? l_n_size : this->m_n_max;
    PoolDataClass* g_po_pd = new PoolDataClass(l_n_block, 
                                                this->m_po_pd_small->GetFilePath(),
                                                this->m_po_pd_small->GetFileName()
                                                );
    if(g_po_pd->m_puch_last){
        l_puch_addr = g_po_pd->m_puch_last;
        PoolPartClass* g_po_pp = new PoolPartClass();
        g_po_pp->m_puch_start = g_po_pd->m_puch_last;
        g_po_pd->m_puch_last += l_n_size;
        g_po_pp->m_puch_end = g_po_pd->m_puch_last;
        g_po_pd->setsize(g_po_pd->getsize() + l_n_size);
        if(g_po_pd->m_po_pp_tail){
            g_po_pd->m_po_pp_tail = g_po_pp;
        }else{
            g_po_pp->m_po_pp_pre = g_po_pd->m_po_pp_tail;
            g_po_pd->m_po_pp_tail = g_po_pp;
        }
        PoolDataClass* l_po_pd_q = l_n_type ? this->m_po_pd_large : this->m_po_pd_small;
        while(l_po_pd_q->m_po_pd_next) l_po_pd_q = l_po_pd_q->m_po_pd_next;
        l_po_pd_q->m_po_pd_next = g_po_pd;
        this->m_n_small_len = l_n_type ? this->m_n_small_len : (++this->m_n_small_len);
        this->m_n_large_len = l_n_type ? (++this->m_n_large_len) : this->m_n_large_len;
        g_o_pr.m_po_pd_alloc = g_po_pd;
        g_o_pr.m_puch_addr = l_puch_addr;
    }
}

void PoolClass::AllocLarge(PoolRetClass& g_o_pr, size_t l_n_size){
    u_char* l_puch_addr = NULL;
    if(!this->m_po_pd_large){
        this->m_po_pd_large = new PoolDataClass(l_n_size, 
                                                this->m_po_pd_small->GetFilePath(),
                                                this->m_po_pd_small->GetFileName()
                                                );
        if(this->m_po_pd_large->m_puch_last){
            l_puch_addr = this->m_po_pd_large->m_puch_last;
            PoolPartClass* g_po_pp = new PoolPartClass();
            g_po_pp->m_puch_start = this->m_po_pd_large->m_puch_last;
            this->m_po_pd_large->m_puch_last += l_n_size;
            g_po_pp->m_puch_end = this->m_po_pd_large->m_puch_last;
            this->m_po_pd_large->setsize(this->m_po_pd_large->getsize() + l_n_size);
            if(this->m_po_pd_large->m_po_pp_tail){
                this->m_po_pd_large->m_po_pp_tail = g_po_pp;
            }else{
                g_po_pp->m_po_pp_pre = this->m_po_pd_large->m_po_pp_tail;
                this->m_po_pd_large->m_po_pp_tail = g_po_pp;
            }
        }else{
            this->m_po_pd_large = NULL;
        }
        g_o_pr.m_po_pd_alloc = this->m_po_pd_large;
        g_o_pr.m_puch_addr = l_puch_addr;
    }else{
        this->Allocblock(g_o_pr, l_n_size,1);
    }
}

//ContainerBaseClass
ContainerBaseClass::ContainerBaseClass(PoolClass& g_o_p, size_t l_n_size)
    :m_o_pr(),m_puch_start(NULL),m_puch_end(NULL),m_n_size(l_n_size)
{
    g_o_p.alloc(this->m_o_pr, l_n_size);
    this->m_puch_start = this->m_o_pr.m_puch_addr;
    this->m_puch_end = this->m_puch_start + l_n_size;
}

ContainerBaseClass::~ContainerBaseClass(){
    PoolDataClass* l_po_pd = this->m_o_pr.m_po_pd_alloc;
    PoolPartClass* l_po_pp = l_po_pd->m_po_pp_tail;
    while(l_po_pp){
        if(l_po_pp->m_puch_start == this->m_puch_start){
            l_po_pp->m_n_status = 0;
            std::memset(this->m_puch_start,0,this->m_n_size);
            this->m_o_pr.m_po_pd_alloc->recycle();
            break;
        }
        l_po_pp = l_po_pp->m_po_pp_pre;
    }
    this->m_puch_start = NULL;
    this->m_puch_end   = NULL;
    this->m_n_size  = 0;
}