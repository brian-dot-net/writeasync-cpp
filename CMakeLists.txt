cmake_minimum_required (VERSION 3.15)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("writeasync-cpp")

add_compile_options(/W4)

enable_testing()

add_subdirectory(src)
