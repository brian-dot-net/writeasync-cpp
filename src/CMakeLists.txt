add_library(decorator-core
    "decorator/lib/coin.cpp"
    "decorator/lib/coin_invert.cpp"
    "decorator/lib/coin_trace.cpp"
    "decorator/lib/trace.cpp"
    "decorator/lib/trace_header.cpp"
)

target_compile_features(decorator-core PUBLIC cxx_std_20)

target_include_directories(decorator-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/decorator/inc
)

add_executable(decorator-app
    "decorator/exe/main.cpp"
)

target_compile_features(decorator-app PUBLIC cxx_std_20)

target_link_libraries(decorator-app
    decorator-core
)

find_package(GTest REQUIRED)

add_executable(decorator-test
    "decorator/test/coin_test.cpp"
    "decorator/test/coin_trace_test.cpp"
    "decorator/test/trace_test.cpp"
    "decorator/test/trace_header_test.cpp"
)

target_compile_features(decorator-test PUBLIC cxx_std_20)

target_link_libraries(decorator-test
    decorator-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(decorator-test)
