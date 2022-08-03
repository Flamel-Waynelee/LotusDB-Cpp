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

class Memtable {
    Memtable(uint32_t file_id) : file_id_(file_id) {
        filename_ = ROOT_DIR + "vl" + std::string(std::to_string(file_id)) + ".vl";
        fp_ = fopen(filename_.c_str(), "rb+");
        if (fp_ == NULL)
            fp_ = fopen(filename_.c_str(), "wb");
        else 
            reload();
    }

    ~Memtable() {
        fclose(fp_); 
    }

    void write(const std::string& key, const std::string& value) {
        rwlock_.wrlock();
        WalEntry wal_entry(key, value);
        wal_entry.write(fp_);
        rwlock_.unlock();
    }

    WalEntry read() {
        rwlock_.rdlock();
        WalEntry wal_entry(fp_);
        rwlock_.unlock();
        return wal_entry;
    }

    uint32_t size() {
        rwlock_.rdlock();
        uint32_t ret = ftell(fp_);
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
    uint32_t file_id_;
    std::string filename_;
    FILE* fp_;
};

#endif
