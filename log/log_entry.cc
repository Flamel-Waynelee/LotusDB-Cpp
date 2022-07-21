/**
 * @file log_entry.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief LogEntry类的实现
 * @date 2022-07-21
 */
#include "log_entry.h"
#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <cstring>
#include <strings.h>

using namespace std;

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

bool Header::get_bytes(uint8_t *buffer, int max_len) const {
    if (max_len < HEADER_SIZE)
        return false;

    bzero(buffer, HEADER_SIZE);
    uint8_t index = 0;
    *((uint32_t*)(&buffer[index])) = crc;
    index += CRC_SIZE;
    *((uint32_t*)(&buffer[index])) = type;
    index += TYPE_SIZE;
    *((uint32_t*)(&buffer[index])) = key_size;
    index += KEY_SIZE_SIZE;
    *((uint32_t*)(&buffer[index])) = value_size;
    index += VALUE_SIZE_SIZE;
    *((uint32_t*)(&buffer[index])) = expiration;

    return true;
}

bool LogEntry::get_bytes(uint8_t *buffer, int max_len) const {
    if (!header_.get_bytes(buffer, max_len))
        return false;
    if (max_len - HEADER_SIZE < header_.key_size + header_.value_size)
        return false;
    memcpy(buffer + HEADER_SIZE, key_, header_.key_size);
    memcpy(buffer + HEADER_SIZE + header_.key_size, value_, header_.value_size);
    return true;
}

LogEntry::LogEntry(uint8_t* bytes, int len) {
    if (len < HEADER_SIZE) {
        STDERR_FUNC_LINE();
        exit(EXIT_FAILURE);
    }

    uint8_t index = 0;

    header_.crc = *((uint32_t*)(&bytes[index]));
    index += CRC_SIZE;
    header_.type = *((uint8_t*)(&bytes[index]));
    index += TYPE_SIZE;
    header_.key_size = *((uint32_t*)(&bytes[index]));
    index += KEY_SIZE_SIZE;
    header_.value_size = *((uint32_t*)(&bytes[index]));
    index += VALUE_SIZE_SIZE;
    header_.expiration = *((int64_t*)(&bytes[index]));
    index += EXPIRATION_SIZE;

    if (len < HEADER_SIZE + header_.key_size + header_.value_size) 
        return;
    
    key_ = (char*)malloc(header_.key_size);
    value_ = (char*)malloc(header_.value_size);
    memcpy(key_, &bytes[index], header_.key_size);
    index += header_.key_size;
    memcpy(value_, &bytes[index], header_.value_size);
}


LogEntry::LogEntry(const char key[], const char value[]) {
    // TODO: 初始化header
    header_.crc = 0;
    header_.type = 0;
    header_.key_size = strlen(key);
    header_.value_size = strlen(value);
    header_.expiration = 0;

    key_ = strdup(key);
    value_ = strdup(value);
}

LogEntry::LogEntry(const LogEntry& log_entry) : header_(log_entry.header_) {
    key_ = strdup(log_entry.key_);
    value_ = strdup(log_entry.value_);
}

LogEntry& LogEntry::operator=(const LogEntry &log_entry) {
    if (this == &log_entry)
        return *this;
    header_ = log_entry.header_;
    free(key_);
    free(value_);
    key_ = strdup(log_entry.key_);
    value_ = strdup(log_entry.value_);
    return *this;
}

LogEntry::~LogEntry() {
    free(key_);
    free(value_);
}
