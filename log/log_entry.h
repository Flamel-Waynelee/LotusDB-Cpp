/**
 * @file log_entry.h
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief LogEntry类
 * @date 2022-07-21
 */
#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include "pch.h"
#include <bits/stdint-uintn.h>
#include <cstdio>

/**
 * @brief 
 * The LogEntry looks like:
 * +-------+--------+----------+------------+------------+-------+---------+
 * |  crc  |  type  | key_size | value_size | expiration |  key  |  value  |
 * +-------+--------+----------+------------+-------------+-------+---------+
 * |------------------------HEADER-----------------------|
 *         |--------------------------crc check---------------------------|
 * |---4---|---1----|----5-----|-----5------|-----10-----|
 * |-------------------------25--------------------------|
 */
enum Size {
    CRC_SIZE = 4,
    TYPE_SIZE = 1,
    KEY_SIZE_SIZE = 5,
    VALUE_SIZE_SIZE = 5,
    EXPIRATION_SIZE = 10
};
constexpr uint8_t HEADER_SIZE = 25;

struct Header {
    bool get_bytes(uint8_t* buffer, int max_len) const;

    uint32_t crc;
    uint8_t type;
    uint32_t key_size;
    uint32_t value_size;
    int64_t expiration;
};

class LogEntry {
public:
    LogEntry(const char key[], const char value[]);
    LogEntry(uint8_t* bytes, int len);

    LogEntry(const LogEntry& log_entry);
    LogEntry& operator=(const LogEntry& log_entry);
    ~LogEntry();

    bool get_bytes(uint8_t* buffer, int max_len) const;

    void debug_show() const {
        STDERR("%04x %02x %04x %04x %08lx", header_.crc, header_.type, header_.key_size, header_.value_size, header_.expiration);
    }

private:
    Header header_;
    char* key_;
    char* value_;
};

#endif