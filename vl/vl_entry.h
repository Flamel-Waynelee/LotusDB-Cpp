#ifndef VL_ENTRY_H
#define VL_ENTRY_H

#include "pch.h"
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

struct VL_HEADER {
    VL_HEADER() : crc(0), value_size(0) { }

    uint32_t crc;
    uint32_t value_size;
};

class VlEntry {

private:
    VL_HEADER vl_header_;
    std::string value_;
};

#endif
