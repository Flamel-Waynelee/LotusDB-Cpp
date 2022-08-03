#ifndef LOTUS_DB_H
#define LOTUS_DB_H

#include "pch.h"

#include "lock.h"
#include "memtable.h"
#include "wal_entry.h"
#include "config.h"
#include <queue>
#include <string>

class LotusDb {
public:


private:
    // Memtable active_memtable_;
    // std::queue<Memtable> immutable_memtables_;   
};

#endif
