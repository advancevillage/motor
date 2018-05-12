/*
 * Copyright (C) Richard Sun
 */

#include <mtr_config.h>
#include <mtr_core.h>

void* mtr_alloc(size_t size, mtr_log_t *log){
	void *p = NULL;
	p = malloc(size);
	if ( NULL ==  p) {
		mtr_log_error(MTR_LOG_EMERG, log, 1, "malloc(%uz) failed", size);
	}
	return p;

}
