/**
 * @file wal_entry.h
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalEntry类
 * @date 2022-07-21
 */
#ifndef WAL_ENTRY_H
#define WAL_ENTRY_H

#include "pch.h"
#include <bits/stdint-uintn.h>
#include <bits/types/time_t.h>
#include <cstdio>
#include <string>
#include <utility>

/**
 * @brief 
 * The WalEntry looks like:
 * +-------+-----------+----------+------------+-------+---------+
 * |  crc  | timestamp | key_size | value_size |  key  |  value  |
 * +-------+-----------+----------+------------+-------+---------+
 * |------------------HEADER-------------------|
 *         |----------------------crc check----------------------|
 * |---4---|-----4-----|----4-----|-----4------|
 * |--------------------16---------------------|
 */

constexpr uint8_t ITEM_SIZE = 4;
constexpr uint8_t WAL_HEADER_SIZE = 16;

using MemEntry = std::pair<std::string, std::pair<std::string, time_t>>;

struct WalHeader {
public:
    WalHeader() : crc(0), timestamp(0), key_size(0), value_size(0) { }

    uint32_t crc;
    time_t timestamp;
    uint32_t key_size;
    uint32_t value_size;
};

class WalEntry {
public:
    WalEntry() : key_(NULL), value_(NULL) { }
    WalEntry(const char key[], const char value[]);
    WalEntry(FILE* fp);

    WalEntry(const WalEntry& wal_entry);
    WalEntry& operator=(const WalEntry& wal_entry);

    WalEntry(WalEntry&& wal_entry);
    WalEntry& operator=(WalEntry&& wal_entry);

    ~WalEntry();

    bool empty() const {
        return key_ == NULL && value_ == NULL;
    }

    MemEntry get_entry() const {
        return std::pair<std::string, std::pair<std::string, time_t>>(key_, 
            std::pair<std::string, time_t>(value_, wal_header_.timestamp));
    }

    bool get_bytes(uint8_t* buffer, uint32_t max_len) const;

private:
    WalHeader wal_header_;
    char* key_;
    char* value_;
};

#endif