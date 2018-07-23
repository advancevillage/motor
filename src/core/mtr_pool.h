/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_MEM_INCLUDE_H_
#define _MTR_MEM_INCLUDE_H_

#include <mtr_config.h>
#include <mtr_core.h>
/**
 *@brief: memory pool base class
 */
class MtrPoolBaseClass {
public:
    u_char  *start;
protected:
    size_t  failed;
    size_t  max; //unit B
    size_t  size; //unit B
    /**
     *@brief: default log/
     *@note: must end with / 
     */
    std::string filedir; 
    /**
     *@brief: default error.log
     */
    std::string filename;

public:
    explicit MtrPoolBaseClass(std::string _filedir = "log/", std::string filename = "error.log");
    explicit MtrPoolBaseClass(size_t _size, std::string _filedir = "log/", std::string filename = "error.log");
    ~MtrPoolBaseClass();

public:
    /**
     *@brief: Get the size of the allocated memory
     *@brief: unit B
     */
    size_t GetSize() const;
    /**
     *@brief: Get the size of the remaining memory in the allocated memory
     *@brief: unit B
     */
    size_t GetFreeSize() const;
    void   SetFreeSize(size_t _max);
    /**
     *@brief: Get the log file
     */
    std::string GetLogFile() const;
    /**
     *@brief: Initialize memory allocation
     *@param: size_t _size = 2^n
     *@retal: the first address of the memory allocation
     */
    void Initialize(size_t _size = 0);
    /**
     *@brief: Get allocate memory failed num
     */
    size_t GetFailed() const;
};
/**
 *@brief: partition of pool
 */
class MtrPoolPartClass {
public:
    u_char  *start;
    u_char  *end;
    /**
     *@brief: [0|1] 0: Recyclable 1: in-used
     */
    mtr_uint_t  status;
    MtrPoolPartClass    *pre;
public:
    explicit MtrPoolPartClass(u_char *_start = NULL, u_char *_end = NULL, mtr_uint_t _status = 1);
    ~MtrPoolPartClass();

};
/**
 *@brief: memory pool data
 */ 
class MtrPoolDataClass : public MtrPoolBaseClass {
public:
    u_char              *last;
    u_char              *end;
    MtrPoolPartClass    *tail;
public:
    MtrPoolDataClass    *next;
public:
    explicit MtrPoolDataClass(std::string _filedir = "log/", std::string filename = "error.log");
    explicit MtrPoolDataClass(size_t _size, std::string _filedir = "log/", std::string filename = "error.log");
    ~MtrPoolDataClass();
    /**
     *@brief: recycle pool data memory
     *@brief: reset and status == 0 before call
     */
    void MtrPoolDataRecycle();
};

/**
 * @brief: memory pool
 */
class MtrPoolClass {
public:
    MtrPoolDataClass    *small;
    MtrPoolDataClass    *large;
protected:
    LogProcessor        *log;
    size_t  smallen;
    size_t  largelen;
    size_t  max;

public:
    explicit MtrPoolClass(LogProcessor *_log, size_t _max);
    ~MtrPoolClass();

public:
    /**
     *@brief: allocate memory 
     *@param: byte
     */
    u_char* MtrAllocPool(size_t _size);
    /**
     *@brief: Get max size
     */
    size_t GetMaxSize() const;
    /**
     *@brief Get Small Pool list length
     */
    size_t GetSmallPoolListLength() const;
    /**
     *@brief: Get Large Pool list length
     */
    size_t GetLargePoolListLength() const;

private:
    u_char* MtrAllocSmallPool(size_t _size);
    u_char* MtrAllocLargePool(size_t _size);
    /**
     *@brief: Extended memory pool
     *@param: type [0|1]
     */
    u_char* MtrAllocblock(size_t _size, size_t type = 0);

};

#endif