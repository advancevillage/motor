/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>

BufferClass::BufferClass(PoolClass& g_o_p, size_t l_n_size)
    :ContainerBaseClass(g_o_p, l_n_size), m_puch_pos(NULL),m_puch_last(NULL),m_n_len(0)
{
    this->m_puch_pos = this->m_puch_start;
    this->m_puch_last = this->m_puch_start;
}

BufferClass::~BufferClass(){
    this->m_puch_pos = NULL;
    this->m_puch_last = NULL;
    this->m_n_len = 0;
}

bool BufferClass::in(void* l_p_src, size_t l_n_size){
    if((this->m_n_size - this->m_n_len) < l_n_size ){
        return false;
    }
    std::memcpy(this->m_puch_last, l_p_src, l_n_size);
    this->m_puch_last = this->m_puch_last + l_n_size;
    this->m_n_len += l_n_size;
    return true;
}

bool BufferClass::in(const void* l_p_src, size_t l_n_size){
    if((this->m_n_size - this->m_n_len) < l_n_size ){
        return false;
    }
    std::memcpy(this->m_puch_last, l_p_src, l_n_size);
    this->m_puch_last = this->m_puch_last + l_n_size;
    this->m_n_len += l_n_size;
    return true;
}

bool BufferClass::in(std::string l_str_msg){
    return this->in(l_str_msg.data(), l_str_msg.length());
}

bool BufferClass::operator<<(std::string l_str_msg){
    return this->in(l_str_msg.data(), l_str_msg.length());
}

bool BufferClass::out(std::string l_str_file){
    std::ofstream l_o_fs;
    l_o_fs.open(l_str_file, std::ofstream::out | std::ofstream::app);
    l_o_fs.write((char*)this->m_puch_pos,this->m_n_len);
    l_o_fs.close();
    return true;
}

bool BufferClass::operator>> (std::string l_str_file){
    return this->out(l_str_file);
}

void BufferClass::reset(){
    std::memset(this->m_puch_pos, 0, this->m_n_len);
    this->m_puch_last = this->m_puch_pos;
    this->m_n_len = 0;
}