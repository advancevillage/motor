/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_CONFIG_H_INCLUDE_
#define _MTR_CONFIG_H_INCLUDE_

#include <mtr_auto_headers.h>

#if (MTR_LINUX)
#include <mtr_linux_config.h>
#endif

typedef intptr_t  mtr_int_t;  //!< <stdint.h> 
typedef uintptr_t mtr_uint_t; 
typedef int		  mtr_fd_t;
typedef int		  mtr_err_t;

#ifndef mtr_inline
#define mtr_inline	inline
#endif

#define MTR_INT32_LEN  (sizeof("-2147483648") - 1) 
#define MTR_INT64_LEN  (sizeof("-9223372036854775808") - 1) 

#endif
