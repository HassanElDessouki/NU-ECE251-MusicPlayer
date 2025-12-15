cmake_minimum_required(VERSION 3.30)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "C:/dev/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Find TagLib package
find_package(TagLib REQUIRED)

add_executable(MusicPlayer main.cpp song.cpp playlist.cpp)

# Link TagLib to the executable
target_link_libraries(MusicPlayer PRIVATE TagLib::tag)