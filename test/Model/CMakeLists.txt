add_executable(image_util_test
    ImageUtilTest.cpp
)

target_link_libraries(image_util_test
    PRIVATE model
)