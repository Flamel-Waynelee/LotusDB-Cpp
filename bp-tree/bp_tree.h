#ifndef BP_TREE_H
#define BP_TREE_H

#include "pch.h"
#include <bits/stdint-uintn.h>

struct Meta {
    Meta() : timestamp(0), file_id(0), offset(0) { }

    time_t timestamp;
    uint32_t file_id;
    uint32_t offset;
};

class BpTree {

};

#endif
