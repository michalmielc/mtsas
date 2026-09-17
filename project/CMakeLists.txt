
cmake_minimum_required(VERSION 3.13)

project(mtsas)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mtsas 
    src/file_Import.cpp
    src/main.cpp
    src/sensor.cpp
    src/measurement.cpp
)

target_include_directories(mtsas PRIVATE include)


target_link_libraries(mtsas PRIVATE stdc++exp)