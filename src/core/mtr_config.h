/*
 * Copyright (C) Richard Sun
 */

#ifndef _OJY_CONFIG_H_INCLUDE_
#define _OJY_CONFIG_H_INCLUDE_

#include <ojy_auto_headers.h>

#if (OJY_LINUX)
#include <ojy_linux_config.h>
#endif

typedef intptr_t  ojy_int_t;  //!< uintptr_t and  intptr_t in <sys/types.h> 
typedef uintptr_t ojy_uint_t; 
typedef intptr_t  ojy_flag_t; 

#define OJY_INT32_LEN  (sizeof("-2147483648") - 1) 
#define OJY_INT64_LEN  (sizeof("-9223372036854775808") - 1) 

#endif
