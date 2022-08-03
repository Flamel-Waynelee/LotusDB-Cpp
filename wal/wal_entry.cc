/**
 * @file wal_entry.cc
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalEntry类的实现
 * @date 2022-07-21
 */
#include "wal_entry.h"
#include "config.h"
#include "pch.h"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <strings.h>
#include <sys/types.h>

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

void WalEntry::write(FILE* fp) const {
    fwrite(&wal_header_, sizeof(wal_header_), 1, fp);
    fwrite(key_.c_str(), sizeof(char), wal_header_.key_size, fp);
    fwrite(value_.c_str(), sizeof(char), wal_header_.value_size, fp);
    fflush(fp);
}

WalEntry::WalEntry(FILE* fp) {
    if (fread(&wal_header_, sizeof(wal_header_), 1, fp) < 1)
        return;

    char buffer[PAGE_SIZE];

    bzero(buffer, sizeof(buffer));
    fread(buffer, sizeof(char), wal_header_.key_size, fp);
    key_ = buffer;

    bzero(buffer, sizeof(buffer));
    fread(buffer, sizeof(char), wal_header_.value_size, fp);
    value_ = buffer;
}

WalEntry::WalEntry(const std::string& key, const std::string& value) : key_(key), value_(value) {
    // TODO: crc
    wal_header_.crc = 0;
    wal_header_.timestamp = time(NULL);
    wal_header_.key_size = key_.size();
    wal_header_.value_size = value_.size();
}

