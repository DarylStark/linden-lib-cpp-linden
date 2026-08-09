cmake_minimum_required(VERSION 4.2)
project(cpp-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Application source
add_subdirectory(src)
