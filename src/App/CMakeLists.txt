add_library(app
        appprocess.cpp
        )

target_include_directories(app
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(app
        PUBLIC model view viewmodel
        )