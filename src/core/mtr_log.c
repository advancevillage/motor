/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

static mtr_str_t err_levels[] = {
    mtr_null_string,
    mtr_string("emerg"),
    mtr_string("alert"),
    mtr_string("crit"),
    mtr_string("error"),
    mtr_string("warn"),
    mtr_string("notice"),
    mtr_string("info"),
    mtr_string("debug")
};

static mtr_str_t debug_levels[] = {
    mtr_null_string,
    mtr_string("debug_core")
};


void mtr_log_error_core(mtr_uint_t level, mtr_log_t *log, mtr_err_t err, const char *fmt, ...){
    u_char *p;
    ssize_t n;
    u_char errstr[MTR_MAX_ERROR_STR];
    p = mtr_cpymem(errstr, log->data.data, log->data.len);
    n = mtr_write_fd(log->file.fd, errstr, p - errstr);
}
