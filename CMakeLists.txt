cmake_minimum_required (VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("writeasync-cpp")

enable_testing()

add_subdirectory(src)
