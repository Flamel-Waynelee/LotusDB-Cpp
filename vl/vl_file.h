#ifndef VL_FILE_H
#define VL_FILE_H

#include "config.h"
#include "vl_entry.h"
#include "lock.h"
#include "pch.h"
#include "bp_tree.h"
#include <bits/stdint-uintn.h>
#include <cstdio>

class VlFile {
public:
    static VlEntry read(uint32_t file_id, uint32_t offset) {
        FILE* fp = fopen((ROOT_DIR + std::to_string(file_id) + ".vl").c_str(), "rb");
        return VlEntry(fp);
    }

    VlFile(uint32_t file_id) : file_id_(file_id) {
        filename_ = ROOT_DIR + std::to_string(file_id) + ".vl";
        fp_ = fopen(filename_.c_str(), "rb+");
        if (fp_ == NULL)
            fp_ = fopen(filename_.c_str(), "wb");
        else 
            fseek(fp_, 0, SEEK_END);
    }

    Meta write(const std::string& value) {
        rwlock_.wrlock();

        Meta meta;
        meta.file_id = file_id_;
        meta.offset = size();

        VlEntry vl_entry(value);
        vl_entry.write(fp_);
        rwlock_.unlock();

        return meta;
    }

    uint32_t size() {
        rwlock_.rdlock();
        uint32_t ret = ftell(fp_);
        rwlock_.unlock();
        return ret;
    }

private:
    RwLock rwlock_;
    uint32_t file_id_;
    std::string filename_;
    FILE* fp_;
};

#endif
