cmake_minimum_required(VERSION 3.22)
project(RpnKalc C)

set(CMAKE_C_STANDARD 11)

add_executable(RpnKalc main.c)
target_link_libraries(RpnKalc m) # flag -lm
