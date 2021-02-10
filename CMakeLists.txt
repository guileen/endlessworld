cmake_minimum_required(VERSION 3.14)
message("version" ${CMAKE_VERSION} )
project(endlessworld VERSION 0.1.0)

# 编译选项
if(MSVC)
  add_compile_options( /W4 /WX)
else()
  #  add_compile_options (-fdiagnostics-color=always) #GNU
  add_compile_options(-w -fcolor-diagnostics) #Clang
endif()

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# GLM
# find_package(glm REQUIRED)
# add_subdirectory(thirdparty/glm)

find_package(glfw3 3.3 REQUIRED)

# GLAD
# add_library(GLAD "thirdparty/glad/glad.c")

find_package(Boost REQUIRED)

include(FetchContent)

# Formatting library, adds fmt::fmt
# FetchContent_Declare(
#   fmtlib
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG 7.0.2)
# FetchContent_MakeAvailable(fmtlib)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)

file(
	GLOB IMGUI_SRC
		"${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
		"${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
		"${IMGUI_DIR}/imgui.cpp"
		"${IMGUI_DIR}/imgui_draw.cpp"
		"${IMGUI_DIR}/imgui_demo.cpp"
		"${IMGUI_DIR}/imgui_tables.cpp"
		"${IMGUI_DIR}/imgui_widgets.cpp"
		# "${IMGUI_DIR}/*.h"
)

include_directories(
  "${CMAKE_SOURCE_DIR}/include"
  # 使用源码导入
  "${CMAKE_SOURCE_DIR}/thirdparty/glm"
  "${CMAKE_SOURCE_DIR}/thirdparty/stb"
  "${CMAKE_SOURCE_DIR}/thirdparty/imgui"
  "${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends"
  "${CMAKE_SOURCE_DIR}/thirdparty/assimp/include"
)

add_subdirectory(thirdparty/assimp)

add_subdirectory(src)

add_subdirectory(apps)

# Testing only available if this is the main app
if(BUILD_TESTING)
  # add_subdirectory(tests)
endif()