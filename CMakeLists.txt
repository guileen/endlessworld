cmake_minimum_required(VERSION 3.0.0)
project(endlessworld VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(glfw3 3.3 REQUIRED)

add_executable(endlessworld main.cpp)
target_link_libraries(endlessworld glfw)
if(APPLE)
    target_link_libraries(endlessworld "-framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon")
endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
