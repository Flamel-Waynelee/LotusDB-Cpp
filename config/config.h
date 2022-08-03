#ifndef CONFIG_H
#define CONFIG_H

#include "pch.h"
#include <bits/stdint-uintn.h>
#include <string>

const std::string ROOT_DIR = "./log/";

constexpr uint32_t PAGE_SIZE = 4096;

struct Config {
    Config() = delete;

};

#endif
