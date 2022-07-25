/**
 * @file wal_entry.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalEntry类的实现
 * @date 2022-07-21
 */
#include "wal_entry.h"
#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <cstring>
#include <strings.h>

using namespace std;

/**
 * @brief 
 * The WalEntry looks like:
 * +-------+--------+----------+------------+------------+-------+---------+
 * |  crc  |  type  | key_size | value_size | expiration |  key  |  value  |
 * +-------+--------+----------+------------+-------------+-------+---------+
 * |------------------------HEADER-----------------------|
 *         |--------------------------crc check---------------------------|
 * |---4---|---1----|----5-----|-----5------|-----10-----|
 * |-------------------------25--------------------------|
 */


bool WalEntry::get_bytes(uint8_t *buffer, uint32_t max_len) const {
    if (max_len < HEADER_SIZE)
        return false;
    memcpy(buffer, &header_, HEADER_SIZE);
    if (max_len - HEADER_SIZE < header_.key_size + header_.value_size)
        return false;
    memcpy(buffer + HEADER_SIZE, key_, header_.key_size);
    memcpy(buffer + HEADER_SIZE + header_.key_size, value_, header_.value_size);
    return true;
}

WalEntry::WalEntry(uint8_t* bytes, uint32_t len) {
    if (len < HEADER_SIZE) {
        STDERR_FUNC_LINE();
        exit(EXIT_FAILURE);
    }

    uint8_t index = 0;
    header_ = *((Header*)bytes);
    index += HEADER_SIZE;

    if (len < HEADER_SIZE + header_.key_size + header_.value_size) 
        return;
    
    key_ = (char*)malloc(header_.key_size);
    value_ = (char*)malloc(header_.value_size);
    memcpy(key_, &bytes[index], header_.key_size);
    index += header_.key_size;
    memcpy(value_, &bytes[index], header_.value_size);
}


WalEntry::WalEntry(const char key[], const char value[]) {
    // TODO: 初始化header
    header_.crc = 0;
    header_.type = 0;
    header_.key_size = strlen(key);
    header_.value_size = strlen(value);
    header_.expiration = 0;

    key_ = strdup(key);
    value_ = strdup(value);
}

WalEntry::~WalEntry() {
    free(key_);
    free(value_);
}
