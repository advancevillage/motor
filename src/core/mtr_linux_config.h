/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_LINUX_CONFIG_H_INCLUDE_
#define _MTR_LINUX_CONFIG_H_INCLUDE_

#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int		mtr_fd_t;

#define MTR_PAGESIZE   (getpagesize())

#endif
