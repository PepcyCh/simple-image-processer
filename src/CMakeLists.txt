add_subdirectory(Common)
add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(ViewModel)
add_subdirectory(Window)
add_subdirectory(App)

add_executable(${PROJECT_NAME}
    main.cpp
)