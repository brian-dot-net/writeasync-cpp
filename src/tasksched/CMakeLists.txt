add_library(tasksched-core
    "lib/todo.cpp"
)

target_compile_features(tasksched-core PUBLIC cxx_std_20)

target_include_directories(tasksched-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

find_package(WIL REQUIRED)

add_executable(tasksched-app
    "exe/main.cpp"
)

target_compile_features(tasksched-app PUBLIC cxx_std_20)

target_link_libraries(tasksched-app
    tasksched-core
    taskschd.lib
    comsupp.lib
    WIL::WIL
)

find_package(GTest REQUIRED)

add_executable(tasksched-test
    "test/todo_test.cpp"
)

target_compile_features(tasksched-test PUBLIC cxx_std_20)

target_link_libraries(tasksched-test
    tasksched-core
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(tasksched-test)
