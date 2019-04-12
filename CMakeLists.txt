cmake_minimum_required(VERSION 3.10)
project(ZTEAlgorithm)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(
        include
)

AUX_SOURCE_DIRECTORY(src DIR_SRCS)

SET(SOURCE_FILES
        ${DIR_SRCS}
        )

add_executable(ZTEAlgorithm ${SOURCE_FILES} main.cpp)
