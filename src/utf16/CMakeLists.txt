add_library(utf16-core
    "lib/todo.cpp"
)

target_compile_features(utf16-core PUBLIC cxx_std_20)

target_include_directories(utf16-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

find_package(Microsoft.GSL REQUIRED)
find_package(WIL REQUIRED)

target_link_libraries(utf16-core
    Microsoft.GSL::GSL
    WIL::WIL
)

add_executable(utf16-app
    "exe/main.cpp"
)

target_compile_features(utf16-app PUBLIC cxx_std_20)

target_link_libraries(utf16-app
    utf16-core
    Microsoft.GSL::GSL
    WIL::WIL
)

find_package(GTest REQUIRED)

add_executable(utf16-test
    "test/todo_test.cpp"
)

target_compile_features(utf16-test PUBLIC cxx_std_20)

target_link_libraries(utf16-test
    utf16-core
    GTest::gtest
    GTest::gtest_main
    Microsoft.GSL::GSL
    WIL::WIL
)

gtest_discover_tests(utf16-test)
