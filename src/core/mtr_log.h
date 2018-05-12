/*
 * Copyright (C) Richard Sun
 */
#ifndef _MTR_LOG_H_INCLUDE_
#define _MTR_LOG_H_INCLUDE_

#include <mtr_config.h>
#include <mtr_core.h>

#define MTR_LOG_STDERR            0  
#define MTR_LOG_EMERG             1  
#define MTR_LOG_ALERT             2  
#define MTR_LOG_CRIT              3  
#define MTR_LOG_ERR               4  
#define MTR_LOG_WARN              5  
#define MTR_LOG_NOTICE            6  
#define MTR_LOG_INFO              7  
#define MTR_LOG_DEBUG             8  

#define MTR_LOG_DEBUG_CORE        0x010  
#define MTR_LOG_DEBUG_ALLOC		  0x020
#define MTR_LOG_DEBUG_MUTEX		  0x040

#define MTR_MAX_ERROR_STR		2048

typedef struct {
	mtr_fd_t	fd;
	mtr_str_t	name;
} mtr_open_file_t;


typedef struct {
	mtr_uint_t			 log_level;
	mtr_open_file_t		 file;
	time_t				 disk_full_time;
	mtr_str_t			 data;
} mtr_log_t;

/*!
 *@brief man 2 write
 *@param  fd 
 *@param  buf
 *@param  n
 *@retval 
 *	-1 is err; 0 is ok
 */
static mtr_inline ssize_t mtr_write_fd(mtr_fd_t fd, void *buf, size_t n){
	return write(fd, buf, n);
}

#define mtr_log_error(level, log, args...)			\
	if ((log)->log_level >= level) mtr_log_error_core(level, log, args)

#define mtr_log_debug(level, log, args...)			\
	if ((log)->log_level & level) mtr_log_error_core(MTR_LOG_DEBUG, log, args)

void mtr_log_error_core(mtr_uint_t level, mtr_log_t *log, mtr_err_t err, const char *fmt, ...);

#endif
