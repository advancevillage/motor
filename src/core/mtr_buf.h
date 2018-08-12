/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_BUF_INCLUDE_H_
#define _MTR_BUF_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

class BufferClass : public ContainerBaseClass {
public:
    u_char* m_puch_pos;
    u_char* m_puch_last;

protected:
    size_t  m_n_len;

public:
    explicit BufferClass(PoolClass& g_o_p, size_t l_n_size);
    ~BufferClass();
    
public:
    bool in(void* l_p_src, size_t l_n_size);
    bool in(const void* l_p_src, size_t l_n_size);
    bool in(std::string l_str_msg);
    bool operator << (std::string l_str_msg);
    bool operator >> (std::string l_str_msg);
    bool out(std::string l_str_file);
    void reset();
};
#endif