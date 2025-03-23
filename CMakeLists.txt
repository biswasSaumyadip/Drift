cmake_minimum_required(VERSION 3.29)
project(SimpleKS)

set(CMAKE_CXX_STANDARD 20)

add_executable(SimpleKS src/main.cpp
        src/utils/color_utils.hpp src/config.hpp
        src/registry.cpp
        src/registry.h
        src/handlers.cpp
        src/handlers.h
        src/keystore.cpp
        src/keystore.h
        src/databaseManager.cpp
        src/databaseManager.h
)
target_include_directories(SimpleKS PRIVATE src)