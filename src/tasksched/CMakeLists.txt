add_library(tasksched-core
    "lib/date_time.cpp"
    "lib/task.cpp"
    "lib/task_folder.cpp"
    "lib/task_service.cpp"
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
    "test/stub_regtask.cpp"
    "test/stub_settings.cpp"
    "test/stub_taskdef.cpp"
    "test/stub_taskfolder.cpp"
    "test/stub_tasksvc.cpp"
    "test/stub_triggers.cpp"
    "test/task_folder_test.cpp"
    "test/task_service_test.cpp"
    "test/task_test.cpp"
)

target_compile_features(tasksched-test PUBLIC cxx_std_20)

target_link_libraries(tasksched-test
    tasksched-core
    taskschd.lib
    GTest::gtest
    GTest::gtest_main
    WIL::WIL
)

gtest_discover_tests(tasksched-test)
