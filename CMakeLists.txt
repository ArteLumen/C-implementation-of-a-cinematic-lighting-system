# 1. Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# 2. Project name and programming language
project(CinematicLightSimulator VERSION 1.0 LANGUAGES CXX)

# 3. Set C++ standard (C++11 or higher)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Define the executable and list all source/header files
add_executable(light_sim
    main.cpp
    CinematicLight.cpp
    CinematicLight.h
    Vector3.h
)
