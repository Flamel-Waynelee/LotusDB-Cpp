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
#include <bits/types/FILE.h>
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
    WalEntry(const std::string& key, const std::string& value);
    WalEntry(FILE* fp);

    void write(FILE* fp) const;

    bool empty() const {
        return key_.empty() && value_.empty();
    }

    std::pair<std::string, std::pair<std::string, time_t>> get_entry() const {
        return std::pair<std::string, std::pair<std::string, time_t>>(key_, 
            std::pair<std::string, time_t>(value_, wal_header_.timestamp));
    }


private:
    WalHeader wal_header_;
    std::string key_;
    std::string value_;
};

#endif