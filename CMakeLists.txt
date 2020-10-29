cmake_minimum_required(VERSION 3.16)
project(lexical_analysis)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lexical_analysis
        img/shell_capture.gif
        main.c
        perfect.txt
        README.md
        tokens.h)
