cmake_minimum_required(VERSION 4.3)
project(cdis)

find_package(Threads REQUIRED)

add_executable(cdis
    src/main.c
    src/utils.c
    src/rserver.c
)

target_include_directories(cdis PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(cdis PRIVATE ws2_32 Threads::Threads)