/*
 * Copyright (C) Richard Sun
 */

#ifndef _MTR_CORE_INCLUDE_H_
#define _MTR_CORE_INCLUDE_H_
#include <mtr_config.h>

#define MTR_OK			 0
#define MTR_ERROR		-1

//fmt lib 
#ifndef _MTR_USE_FMT_INCLUDE_H_
#define _MTR_USE_FMT_INCLUDE_H_
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/posix.h>
#include <fmt/time.h>
#include <fmt/ranges.h>
#include <fmt/printf.h>
#include <fmt/ostream.h>
#include <fmt/format-inl.h>
#endif

#include <mtr_log.h>

#endif
