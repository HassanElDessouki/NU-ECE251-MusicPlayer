cmake_minimum_required(VERSION 3.30)
project(ECE251)

set(CMAKE_CXX_STANDARD 20)

# Find TagLib package
find_package(TagLib REQUIRED)

add_executable(ECE251 main.cpp)

# Link TagLib to the executable
target_link_libraries(MusicPlayer PRIVATE TagLib::tag)