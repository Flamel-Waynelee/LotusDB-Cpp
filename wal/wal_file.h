/**
 * @file wal_file.h
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalFile类
 * @date 2022-07-26
 */
#ifndef WAL_FILE_H
#define WAL_FILE_H

#include "pch.h"

#include "wal_entry.h"
#include "config.h"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <strings.h>

class WalFile {
public:
    WalFile() {
        strcpy(filename_, root_dir);
        strcat(filename_, "wal");
        fp_ = fopen(filename_, "ab+");
    }

    ~WalFile() {
        fclose(fp_);
        remove(filename_);
    }

    uint32_t write(const char key[], const char value[]) {
        WalEntry wal_entry(key, value);
        uint32_t len = WAL_HEADER_SIZE + strlen(key) + strlen(value);
        uint8_t* buffer = (uint8_t*)malloc(len);
        wal_entry.get_bytes(buffer, len);
        fwrite(buffer, sizeof(uint8_t), len, fp_);
        return len;
    }

    void rewind() {
        ::rewind(fp_);
    }

    WalEntry read() {
        return WalEntry(fp_);
    }

    uint32_t size() const {
        return ftell(fp_);
    }

private:
    char filename_[MAX_FILENAME_LEN];
    FILE* fp_;
};

#endif
