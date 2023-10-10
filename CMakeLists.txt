cmake_minimum_required(VERSION 3.17)

project(proj)

set(CMAKE_CXX_STANDARD 14)

set(CPACK_PACKAGE_FILE_NAME
    "labite"
)

add_executable(proj
        main.cpp
)