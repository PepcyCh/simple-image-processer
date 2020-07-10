add_library(viewmodel
    ImageViewModel.cpp
)

target_include_directories(viewmodel
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(viewmodel
    PUBLIC model
)