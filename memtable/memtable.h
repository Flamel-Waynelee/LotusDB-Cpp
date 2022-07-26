#ifndef MEMTABLE_H
#define MEMTABLE_H

#include "pch.h"
#include "lock.h"
#include "wal_entry.h"
#include "wal_file.h"
#include <bits/types/FILE.h>
#include <bits/types/time_t.h>
#include <map>
#include <string>
#include <utility>


class Memtable {
public:
    Memtable() : size_(0) {
        wal_file_ = new WalFile();
        if (wal_file_->size() > 0)
            reload();
    }

private:
    void reload() {
        rwlock_.wrlock();
        wal_file_->rewind();
        WalEntry wal_entry = wal_file_->read();
        while (!wal_entry.empty())
            index_.insert(wal_entry.get_entry());
        rwlock_.unlock();
    }

    RwLock rwlock_;
    std::map<std::string, std::pair<std::string, time_t>> index_;
    WalFile* wal_file_;
    uint32_t size_;
};

#endif
