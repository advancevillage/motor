/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>
#include <motor.h>

int main(){
	u_char c = 'A';
	u_char c2 = 'b';
	u_char str[100] = "hello motor!";
	printf("str's len is %ld \n", mtr_strlen(str));
	printf("sizeof(u_char) is %ld \n", sizeof(u_char));
	printf("c is %c lower is %c \n", c,mtr_tolower(c));
	printf("c2 is %c lower is %c \n", c2,mtr_tolower(c2));
	printf("c2 is %c upper is %c \n", c2,mtr_toupper(c2));
	printf("c is %c upper is %c \n", c,mtr_toupper(c));
	mtr_int_t  mtr_pagesize = getpagesize();
	printf("mtr_pagesize is %ld\n",mtr_pagesize);
	printf("mtr_pagesize is %ld\n",sizeof(mtr_pagesize));
	printf("mtr_pagesize is %d\n",MTR_PAGESIZE);
    return MTR_OK;
}
