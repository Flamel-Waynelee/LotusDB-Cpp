#ifndef VL_ENTRY_H
#define VL_ENTRY_H

#include "pch.h"
#include "config.h"
#include <bits/stdint-uintn.h>
#include <string>

/**
 * @brief 
 * The VlEntry looks like:
 * +-------+------------+---------+
 * |  crc  | value_size |  value  |
 * +-------+------------+---------+
 * |-------HEADER-------|
 *         |------crc check-------|
 * |---4---|-----4------|
 * |---------16---------|
 */

struct VlHeader {
    VlHeader() : crc(0), value_size(0) { }

    uint32_t crc;
    uint32_t value_size;
};

class VlEntry {
public:
    VlEntry(const std::string& value) : value_(value) {
        //TODO:
        vl_header_.crc = 0;
        vl_header_.value_size = value_.size();
    }

    VlEntry(FILE* fp) {
        if (fread(&vl_header_, sizeof(vl_header_), 1, fp) < 1)
            return;

        char buffer[PAGE_SIZE];
        bzero(buffer, sizeof(buffer));
        fread(buffer, sizeof(char), vl_header_.value_size, fp);
        value_ = buffer;
    }

    void write(FILE* fp) const {
        fwrite(&vl_header_, sizeof(vl_header_), 1, fp);
        fwrite(value_.c_str(), sizeof(char), vl_header_.value_size, fp);
        fflush(fp);
    }

private:
    VlHeader vl_header_;
    std::string value_;
};

#endif
