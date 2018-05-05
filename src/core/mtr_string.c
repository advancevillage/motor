/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

/*!
 *@brief lowercase the first n chracters of the src to dst 
 *@param dst u_char*  
 *@param src u_char* 
 *@param n size_t 
 *@note n is less than len(src) 
 */
void mtr_strlow(u_char *dst, u_char *src, size_t n){
	while(n){
		*dst = mtr_tolower(*src);
		dst++;
		src++;
		n--;
	}
}

/*!
 * brief get str len
 * @param str u_char*
 * @param n   size_t 
 * @retval 
 *       n > strlen(str)  ret strlen(str)
 *       n <= strlen(str) ret n
 */
size_t mtr_strnlen(u_char *str, size_t n){
	size_t i = 0;
	for (i = 0; i < n; ++i){
		if ('\0' == str[i]){
			return i;	
		}
	}
	return n;
}
