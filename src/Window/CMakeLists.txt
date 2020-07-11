add_library(window
        windowprocess.cpp
        )
#set(CMAKE_PREFIX_PATH "D:/Qt/5.14.2/msvc2017/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set_property(
        TARGET window
        PROPERTY AUTOMOC ON
)
set_property(
        TARGET window
        PROPERTY AUTOUIC ON
)
set_property(
        TARGET window
        PROPERTY AUTORCC ON
)

target_include_directories(window
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(window
        PUBLIC model common view viewmodel Qt5::Core Qt5::Gui Qt5::Widgets
        )