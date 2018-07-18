/*
 * Copyright (C) Richard Sun
 */
#include <mtr_config.h>
#include <mtr_core.h>
#include <motor.h>

int main(){
    MtrLogPoolClass mtrlogpooldata;
    MtrLogPoolClass mtrlogpooldata2("logs/error.log");
    MtrLogPoolClass mtrlogpooldata3(1023, "logs/error.log");
    return MTR_OK;
}
