#ifndef LOTUS_DB_H
#define LOTUS_DB_H

#include "pch.h"

#include "lock.h"
#include "wal_entry.h"
#include "wal_file.h"
#include "config.h"
#include <queue>
#include <string>

class LotusDb {
public:
    LotusDb() {
        if (wal_file_.size() > 0)
            reload();
    }

    std::string read(const std::string& key) {
        return active_memtable_[key].first;
    }

    void write(const std::string& key, const std::string& value) {
        if (wal_file_.size() + WAL_HEADER_SIZE + key.size() + value.size() > PAGE_SIZE) {
            // TODO: flush
            wal_file_.reopen();
        }
        active_memtable_.insert(wal_file_.write(key, value));
    }

private:
    void reload() {
        rwlock_.wrlock();
        wal_file_.rewind();
        WalEntry wal_entry = wal_file_.read();
        while (!wal_entry.empty()) {
            active_memtable_.insert(wal_entry.get_entry());
            wal_entry = wal_file_.read();
        }
        rwlock_.unlock();
    }
    
    RwLock rwlock_;
    Memtable active_memtable_;
    std::queue<Memtable> immutable_memtables_;   
    WalFile wal_file_; 
};

#endif
