add_library(window
        windowprocess.cpp
        )

target_include_directories(window
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(window
        PUBLIC model common view viewmodel
        )