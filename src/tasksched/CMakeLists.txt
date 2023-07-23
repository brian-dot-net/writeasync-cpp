add_library(tasksched-core
    "lib/date_time.cpp"
    "lib/task.cpp"
    "lib/task_folder.cpp"
)

target_compile_features(tasksched-core PUBLIC cxx_std_20)

target_include_directories(tasksched-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

find_package(WIL REQUIRED)

target_link_libraries(tasksched-core
    WIL::WIL
)

add_executable(tasksched-app
    "exe/main.cpp"
)

target_compile_features(tasksched-app PUBLIC cxx_std_20)

target_link_libraries(tasksched-app
    tasksched-core
    taskschd.lib
    WIL::WIL
)

find_package(GTest REQUIRED)

add_executable(tasksched-test
    "test/date_time_test.cpp"
    "test/stub_actions.cpp"
    "test/stub_principal.cpp"
    "test/stub_reginfo.cpp"
    "test/stub_settings.cpp"
    "test/stub_taskdef.cpp"
    "test/stub_triggers.cpp"
    "test/task_test.cpp"
)

target_compile_features(tasksched-test PUBLIC cxx_std_20)

target_link_libraries(tasksched-test
    tasksched-core
    GTest::gtest
    GTest::gtest_main
    WIL::WIL
)

gtest_discover_tests(tasksched-test)
