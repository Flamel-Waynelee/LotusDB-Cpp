cmake_minimum_required(VERSION 3.16)

project (LOTUS_DB)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(
    ./log
    ./pch
)

add_executable(LotusDB 
    main.cc 
)
