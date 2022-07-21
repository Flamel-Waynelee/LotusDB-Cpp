/**
 * @file main.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief main函数
 * @date 2022-07-22
 */
#include "log_entry.h"
#include "pch.h"
#include <bits/stdint-uintn.h>

#include <cstdio>
#include <cstring>
#include <strings.h>

int main() {
    LogEntry log_entry("123", "1234");

    uint8_t buffer[40];
    bzero(buffer, 40);
    log_entry.get_bytes(buffer, 40);
    for (uint8_t i = 0; i < 40; i++) 
        STDERR("%02x ", buffer[i]);

    return 0;
}
