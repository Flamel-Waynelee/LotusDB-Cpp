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
#include <bits/types/time_t.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <strings.h>

class WalFile {
public:
    WalFile() {
        filename_ = ROOT_DIR + "wal";
        fp_ = fopen(filename_.c_str(), "rb+");
        if (fp_ == NULL)
            fp_ = fopen(filename_.c_str(), "wb");
        else
            fseek(fp_, 0, SEEK_END);
    }

    ~WalFile() {
        fclose(fp_);
        remove(filename_.c_str());
    }

    void reopen() {
        fclose(fp_);
        fp_ = fopen(filename_.c_str(), "wb");
    }

    MemEntry write(const std::string& key, const std::string& value) {
        WalEntry wal_entry(key, value);
        wal_entry.write(fp_);
        return wal_entry.get_entry();
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
    std::string filename_;
    FILE* fp_;
};

#endif
