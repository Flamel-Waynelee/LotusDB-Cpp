/**
 * @file log_entry.h
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief LogEntry类
 * @date 2022-07-21
 */
#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include "pch.h"

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

struct Header {
    int get_bytes(uint8_t* buffer, int max_len);

    uint32_t crc;
    uint8_t type;
    uint32_t key_size;
    uint32_t value_size;
    int64_t expiration;
};

struct KeyValue {
    int get_bytes(uint8_t* buffer, int max_len);

    uint8_t* key;
    uint8_t* value;
};

class LogEntry {
    enum Size {
        CRC = 4,
        TYPE = 1,
        KEY_SIZE = 5,
        VALUE_SIZE = 5,
        EXPIRATION = 10,
        HEADER = 25
    };

    LogEntry(uint8_t* bytes, int len);

    int get_bytes(uint8_t* buffer, int max_len);

private:
    Header header_;
    KeyValue key_value_;
};

#endif