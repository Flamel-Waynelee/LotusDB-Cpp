#ifndef CONFIG_H
#define CONFIG_H

#include "pch.h"
#include <bits/stdint-uintn.h>

constexpr char root_dir[] = "./log/";
constexpr uint32_t MAX_FILENAME_LEN = 64;

constexpr uint32_t PAGE_SIZE = 4096;

struct Config {
    Config() = delete;

};

#endif
