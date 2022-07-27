cmake_minimum_required(VERSION 3.16)

project (LOTUS_DB)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(
    ./wal
    ./pch
    ./lock
    ./config
)

add_executable(LotusDB 
    main.cc 
    ./wal/wal_entry.cc
)

target_link_libraries(LotusDB pthread)
