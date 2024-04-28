set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(stassert-core
    "lib/example.cpp"
)

target_compile_features(stassert-core PUBLIC cxx_std_20)

target_include_directories(stassert-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(stassert-app
    "exe/main.cpp"
)

target_compile_features(stassert-app PUBLIC cxx_std_20)

target_link_libraries(stassert-app
    stassert-core
)

find_package(GTest REQUIRED)

add_executable(stassert-test
    "test/stassert_test.cpp"
)

target_compile_features(stassert-test PUBLIC cxx_std_20)

target_link_libraries(stassert-test
    stassert-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(stassert-test)