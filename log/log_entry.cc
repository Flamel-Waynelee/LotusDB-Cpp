/**
 * @file log_entry.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief LogEntry类的实现
 * @date 2022-07-21
 */
#include "log_entry.h"

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

/**
 * @brief Construct a new Log Entry:: Log Entry object
 *        
 * @param bytes 
 * @param len 
 */
LogEntry::LogEntry(uint8_t* bytes, int len) {
    if (len < HEADER) {
        STDERR_FUNC_LINE();
        exit(EXIT_FAILURE);
    }

    uint8_t index = 0;

    header_.crc = *((uint32_t*)(&bytes[index]));
    index += CRC;
    header_.type = *((uint8_t*)(&bytes[index]));
    index += TYPE;
    header_.key_size = *((uint32_t*)(&bytes[index]));
    index += KEY_SIZE;
    header_.value_size = *((uint32_t*)(&bytes[index]));
    index += VALUE_SIZE;
    header_.expiration = *((int64_t*)(&bytes[index]));
    index += EXPIRATION;

    if (len < HEADER + header_.key_size + header_.value_size) {
        STDERR_FUNC_LINE();
        exit(EXIT_FAILURE);
    }
    
    memcpy(key_value_.key, &bytes[index], header_.key_size);
    index += header_.key_size;
    memcpy(key_value_.value, &bytes[index], header_.value_size);
}
