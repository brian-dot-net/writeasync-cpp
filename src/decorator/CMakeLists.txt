add_library(decorator-core
    "lib/coin.cpp"
    "lib/coin_invert.cpp"
    "lib/coin_trace.cpp"
    "lib/trace.cpp"
    "lib/trace_header.cpp"
)

target_compile_features(decorator-core PUBLIC cxx_std_20)

target_include_directories(decorator-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(decorator-app
    "exe/main.cpp"
)

target_compile_features(decorator-app PUBLIC cxx_std_20)

target_link_libraries(decorator-app
    decorator-core
)

find_package(GTest REQUIRED)

add_executable(decorator-test
    "test/coin_test.cpp"
    "test/coin_trace_test.cpp"
    "test/trace_test.cpp"
    "test/trace_header_test.cpp"
)

target_compile_features(decorator-test PUBLIC cxx_std_20)

target_link_libraries(decorator-test
    decorator-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(decorator-test)
