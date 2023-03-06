cmake_minimum_required (VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("writeasync-cpp")

add_library(decorator-core
    "src/decorator/lib/coin.cpp"
    "src/decorator/lib/trace.cpp"
)

target_compile_features(decorator-core PUBLIC cxx_std_20)

target_include_directories(decorator-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/decorator/inc
)

add_executable(decorator-app
    src/decorator/exe/main.cpp
)

target_compile_features(decorator-app PUBLIC cxx_std_20)

target_link_libraries(decorator-app
    decorator-core
)

find_package(GTest REQUIRED)

add_executable(decorator-test
    "src/decorator/test/coin_test.cpp"
    "src/decorator/test/trace_test.cpp"
)

target_compile_features(decorator-test PUBLIC cxx_std_20)

target_link_libraries(decorator-test
    decorator-core
    GTest::gtest
    GTest::gtest_main
)

enable_testing()
gtest_discover_tests(decorator-test)
