add_library(stb
    stb_impl.cpp
)

target_include_directories(stb
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)