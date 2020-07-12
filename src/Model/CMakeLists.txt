add_library(model
    ImageModel.cpp
    ImageUtil.cpp
)

target_include_directories(model
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(model
    PUBLIC common
)