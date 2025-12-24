cmake_minimum_required(VERSION 3.10)

# 1. Name your project
project(RiskEngine)

# 2. Set the C++ Standard (nlohmann/json works best with 11 or 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. Tell CMake where to look for .h / .hpp files
# This is equivalent to the "-Iinclude" flag we used earlier
include_directories(../include)

# 4. Create the executable
# "RiskGame" is the output name
# "main.cpp" is your source file
add_executable(RiskEngine Board.hpp Board.cpp Dice.hpp Dice.cpp main.cpp)