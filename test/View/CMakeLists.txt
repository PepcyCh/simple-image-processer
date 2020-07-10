add_executable(mainwnd_test
    MainWindowTest.cpp
)

target_link_libraries(mainwnd_test
    PRIVATE stb view
)