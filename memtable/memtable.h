#ifndef MEMTABLE_H
#define MEMTABLE_H

#include "lock.h"
#include "pch.h"
#include "wal_entry.h"
#include "config.h"
#include <bits/stdint-uintn.h>
#include <bits/types/FILE.h>
#include <cstdio>
#include <string>

class MemTable {
    MemTable(const std::string& filename) : filename_(filename) {
        wal_fp_ = fopen(filename.c_str(), "rb+");
        if (wal_fp_ == NULL)
            wal_fp_ = fopen(filename_.c_str(), "wb");
        else 
            reload();
    }

    ~MemTable() {
        fclose(wal_fp_); 
    }

    void write(const std::string& key, const std::string& value) {
        rwlock_.wrlock();
        WalEntry wal_entry(key, value);
        wal_entry.write(wal_fp_);
        rwlock_.unlock();
    }

    WalEntry read() {
        rwlock_.rdlock();
        WalEntry wal_entry(wal_fp_);
        rwlock_.unlock();
        return wal_entry;
    }

    uint32_t size() {
        rwlock_.rdlock();
        uint32_t ret = ftell(wal_fp_);
        rwlock_.unlock();
        return ret;
    }

private:
    void reload() {
        rwlock_.wrlock();
        WalEntry wal_entry = read();
        while (!wal_entry.empty()) {
            index_.insert(wal_entry.get_entry());
            wal_entry = read();
        }
        rwlock_.unlock();
    }

    RwLock rwlock_;
    std::map<std::string, std::pair<std::string, time_t>> index_;
    std::string filename_;
    FILE* wal_fp_;
};

#endif
