cmake_minimum_required(VERSION 3.10)
project(GameOfLife2)

# Определение стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Путь к SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Источник кода
add_executable(GameOfLife2 main.cpp)

# Линки SDL2
target_link_libraries(GameOfLife2 ${SDL2_LIBRARIES})

