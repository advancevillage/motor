/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_PALLOC_H_INCLUDE_
#define _MTR_PALLOC_H_INCLUDE_

#include <mtr_config.h>
#include <mtr_core.h>

#define MTR_MAX_ALLOC_FROM_POOL  (MTR_PAGESIZE - 1)

#define MTR_DEFAULT_POOL_SIZE    (16 * 1024)

/*!
 *@brief Allocate memory block
 *@param size size_t
 *@param log mtr_log_t*
 *@retval void*
 *@note
 *	(1)Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *	(2)The content of the newly allocated block of memory is not initialized, remaining with indeterminate values.
 *  (3)If size is zero, the return value depends on the particular library implementation (it may or may not be a null pointer), but the returned pointer shall not be dereferenced.
 */
void* mtr_alloc(size_t size, mtr_log_t *log);
void* mtr_calloc(size_t size, mtr_log_t *log);

#endif
