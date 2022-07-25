/**
 * @file wal_file.h
 * @author Flamel-NW (flamel.nw@qq.com)
 * @brief WalFile类
 * @date 2022-07-26
 */
#ifndef WAL_FILE_H
#define WAL_FILE_H

#include "pch.h"
#include <bits/stdint-uintn.h>

class WalFile {

private:
    uint32_t id_;
    FILE* fp_;
};

#endif
