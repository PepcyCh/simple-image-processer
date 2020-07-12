add_library(common
    Image.cpp
    MathUtil.cpp
)

target_include_directories(common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(common
    PUBLIC stb
)