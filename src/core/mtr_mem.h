/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_MEM_INCLUDE_H_
#define _MTR_MEM_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>

/**
 *@brief: pool base class
 */
class PoolBaseClass {
public:
    u_char* m_puch_start;
    u_char* m_puch_end;
protected:
    size_t m_n_capacity;
    size_t m_n_size;
    std::string m_str_filepath;
    std::string m_str_filename;
public:
    explicit PoolBaseClass(std::string l_str_fp = "log/",std::string l_str_fn = "error.log");
    explicit PoolBaseClass(size_t l_n_size = 0, std::string l_str_fp = "log/",std::string l_str_fn = "error.log");
    PoolBaseClass(const PoolBaseClass& g_o_pb);
    virtual ~PoolBaseClass();

    PoolBaseClass& operator= (const PoolBaseClass& g_o_pb);

    virtual size_t getsize() const;
    virtual void setsize(size_t l_n_size);
    virtual size_t capacity() const;
    virtual std::string GetFilePath() const;
    virtual std::string GetFileName() const;
protected:
    void init(size_t l_n_size = 0);
};

/**
 *@brief: partition of pool
 */
class PoolPartClass{
public:
    u_char* m_puch_start;
    u_char* m_puch_end;
    PoolPartClass* m_po_pp_pre;
    /// [0|1] 0: Recyclable 1: in-used
    size_t m_n_status;

public:
    explicit PoolPartClass();
    PoolPartClass(const PoolPartClass& g_o_pp);
    virtual ~PoolPartClass();

    PoolPartClass& operator= (const PoolPartClass& g_o_pp);
};

/**
 *@brief: pool data block
 */
class PoolDataClass : public PoolBaseClass {
public:
    u_char* m_puch_last;

public:
    PoolPartClass* m_po_pp_tail;
    PoolDataClass* m_po_pd_next;

public:
    explicit PoolDataClass(std::string l_str_fp = "log/",std::string l_str_fn = "error.log");
    explicit PoolDataClass(size_t l_n_size = 0, std::string l_str_fp = "log/",std::string l_str_fn = "error.log");
    PoolDataClass(const PoolDataClass& g_o_pd);
    virtual ~PoolDataClass();

    PoolDataClass& operator= (const PoolDataClass& g_o_pd);

    virtual void recycle();
    virtual size_t GetPartCount() const;
};

/**
 *@brief: type of return after allocated memory
 */
class PoolRetClass {
public:
    PoolDataClass* m_po_pd_alloc;
    u_char* m_puch_addr;

public:
    explicit PoolRetClass(PoolDataClass* l_po_pd_alloc = NULL, u_char* l_puch_addr = NULL);
    PoolRetClass(const PoolRetClass& g_o_pr);
    virtual ~PoolRetClass();

    PoolRetClass& operator= (const PoolRetClass& g_o_pr);
};

/**
 *@brief: pool
 */
class PoolClass{
public:
    PoolDataClass* m_po_pd_small;
    PoolDataClass* m_po_pd_large;
protected:
    size_t m_n_small_len;
    size_t m_n_large_len;
    size_t m_n_max;

public:
    explicit PoolClass(std::string l_str_fp = "log/", std::string l_str_fn = "error.log");
    explicit PoolClass(size_t l_n_max = 0, std::string l_str_fp = "log/", std::string l_str_fn = "error.log");
    PoolClass(const PoolClass& g_o_p);
    virtual ~PoolClass();
    PoolClass& operator= (const PoolClass& g_o_p);

    virtual size_t GetSmallPoolLength() const;
    virtual size_t GetLargePoolLength() const;
    virtual size_t max() const;

    virtual void alloc(PoolRetClass& g_o_pr, size_t l_n_size);

private:
    virtual void AllocSmall(PoolRetClass& g_o_pr, size_t l_n_size);
    virtual void AllocLarge(PoolRetClass& g_o_pr, size_t l_n_size);
    /**
     *@brief: Extended memory pool
     *@param: type [0|1]
     */
    virtual void Allocblock(PoolRetClass& g_o_pr, size_t l_n_size, size_t l_n_type = 0);
};

/**
 *@brief: container base class
 */
class ContainerBaseClass{
public:
    PoolRetClass m_o_pr;
    u_char* m_puch_start;
    u_char* m_puch_end;
    size_t  m_n_size;
public:
    explicit ContainerBaseClass(PoolClass& g_o_p, size_t l_n_size);
    virtual ~ContainerBaseClass();
};

#endif