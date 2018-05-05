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

typedef struct {
	mtr_fd_t	fd;
	mtr_str_t	name;
	void       *data;
} mtr_open_file_t;


typedef struct {
	mtr_uint_t			 log_level;
	mtr_open_file_t		*file;
	time_t				 disk_full_time;
	void				*data;
} mtr_lot_t;

#endif
