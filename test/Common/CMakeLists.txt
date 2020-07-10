add_executable(common_test
    CommonTest.cpp
)

target_link_libraries(common_test
    PRIVATE common
)