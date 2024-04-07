add_library(dinject-core
    "lib/todo.cpp"
)

target_compile_features(dinject-core PUBLIC cxx_std_20)

target_include_directories(dinject-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(dinject-app
    "exe/main.cpp"
)

target_compile_features(dinject-app PUBLIC cxx_std_20)

target_link_libraries(dinject-app
    dinject-core
)

find_package(GTest REQUIRED)

add_executable(dinject-test
    "test/todo_test.cpp"
)

target_compile_features(dinject-test PUBLIC cxx_std_20)

target_link_libraries(dinject-test
    dinject-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(dinject-test)
