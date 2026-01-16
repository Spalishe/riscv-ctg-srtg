cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(riscv-ctg-srtg)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")

add_executable(riscv-ctg-srtg ${SOURCES})

set(CMAKE_CXX_FLAGS_DEBUG "-O3 -march=native -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

target_include_directories(riscv-ctg-srtg PRIVATE include)

