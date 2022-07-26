/**
 * @file wal_entry.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalEntry类的实现
 * @date 2022-07-21
 */
#include "wal_entry.h"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <strings.h>

using namespace std;


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

bool WalEntry::get_bytes(uint8_t *buffer, uint32_t max_len) const {
    if (max_len < WAL_HEADER_SIZE)
        return false;
    memcpy(buffer, &wal_header_, WAL_HEADER_SIZE);
    if (max_len - WAL_HEADER_SIZE < wal_header_.key_size + wal_header_.value_size)
        return false;
    memcpy(buffer + WAL_HEADER_SIZE, key_, wal_header_.key_size);
    memcpy(buffer + WAL_HEADER_SIZE + wal_header_.key_size, value_, wal_header_.value_size);
    return true;
}

WalEntry::WalEntry(FILE* fp) {
    key_ = value_ = NULL;
    if (fp == NULL || feof(fp))
        return;
    
    fread(&wal_header_, sizeof(WalHeader), 1, fp);
    fread(key_, sizeof(char), wal_header_.key_size, fp);
    fread(value_, sizeof(char), wal_header_.value_size, fp);
}

WalEntry::WalEntry(const char key[], const char value[]) {
    // TODO: crc
    wal_header_.crc = 0;
    wal_header_.timestamp = time(NULL);
    wal_header_.key_size = strlen(key);
    wal_header_.value_size = strlen(value);

    key_ = strdup(key);
    value_ = strdup(value);
}

WalEntry::WalEntry(const WalEntry& wal_entry) : wal_header_(wal_entry.wal_header_) {
    key_ = strdup(wal_entry.key_);
    value_ = strdup(wal_entry.value_);
}

WalEntry& WalEntry::operator=(const WalEntry &wal_entry) {
    if (this == &wal_entry)
        return *this;
    free(key_);
    free(value_);
    wal_header_ = wal_entry.wal_header_;
    key_ = strdup(wal_entry.key_);
    value_ = strdup(wal_entry.value_);
    return *this;
}

WalEntry::WalEntry(WalEntry&& wal_entry) : wal_header_(wal_entry.wal_header_) {
    key_ = wal_entry.key_;
    value_ = wal_entry.value_;
    wal_entry.key_ = wal_entry.value_ = NULL;
}

WalEntry& WalEntry::operator=(WalEntry&& wal_entry) {
    if (this == &wal_entry)
        return *this;
    free(key_);
    free(value_);
    wal_header_ = wal_entry.wal_header_;
    key_ = wal_entry.key_;
    value_ = wal_entry.value_;
    wal_entry.key_ = wal_entry.value_ = NULL;
    return *this;
}

WalEntry::~WalEntry() {
    if (key_ != NULL)
        free(key_);
    if (value_ != NULL)
        free(value_);
}
