add_library(view
    MainWindow.cpp
)

# change this to yours (where Qt5Config.cmake exists)
set(Qt5_DIR "C:\\Qt\\Qt5.14.2\\5.14.2\\mingw73_64\\lib\\cmake\\Qt5")
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set_property(
    TARGET view
    PROPERTY AUTOMOC ON
)
set_property(
    TARGET view
    PROPERTY AUTOUIC ON
)
set_property(
    TARGET view
    PROPERTY AUTORCC ON
)

target_include_directories(view
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/view_autogen/include
)

target_link_libraries(view
    PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets
)