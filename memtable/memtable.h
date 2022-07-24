#ifndef MEMTABLE_H
#define MEMTABLE_H

#include "pch.h"
#include "lock.h"
#include <bits/types/FILE.h>
#include <map>
#include <string>

class Memtable {

private:
    RwLock rwlock_;
    std::map<std::string, std::string> index;
    FILE* wal;
};

#endif
