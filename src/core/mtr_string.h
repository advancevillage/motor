/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_STRING_H_INCLUDE_
#define _MTR_STRING_H_INCLUDE_

#include <mtr_config.h>
#include <mtr_core.h>

/*!
 *@brief encapsulation string
 *@param len  size_t  
 *@param data u_char*
 */
typedef struct {
	size_t   len;
	u_char  *data;
} mtr_str_t;

#define mtr_string(str)		{ sizeof(str) - 1, (u_char *)str }
#define mtr_null_string		{ 0, NULL }

//! char to lower
#define mtr_tolower(c)		(u_char)(( c >= 'A' && c <= 'Z' ) ? (c | 0x20) : c)
//! char to upper
#define mtr_toupper(c)		(u_char)(( c >= 'a' && c <= 'z' ) ? (c & ~0x20) : c)

//! Copy the first n characters of the src to the dst
void mtr_strlow(u_char *dst, u_char *src, size_t n);
//! Get str len
#define mtr_strlen(s)		strlen((const char *) s)
size_t mtr_strnlen(u_char *str, size_t n);

#define mtr_cpymem(dst, src, n) ((u_char*)memcpy(dst, src, n) + (n))
#define mtr_strcmp(s1, s2)	    strcmp((const char *) s1,(const char *) s2)
#define mtr_strncmp(s1, s2, n)	strncmp((const char *) s1,(const char *) s2, n)
#define mtr_strstr(s1, s2)		strstr((const char *) s1, (const char *) s2)
#define mtr_strchr(s1, c)		strchr((const char *) s1, (int) c)
#define mtr_memcmp(s1, s2, n)   memcmp((const char *) s1, (const char *) s2, n)
#define mtr_memset(buf, c, n)   (void) memset(buf, c, n)
#define mtr_memzero(buf, n)     (void) memset(buf, 0, n)

#endif
