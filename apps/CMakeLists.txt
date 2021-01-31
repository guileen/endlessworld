macro(GLAPP app)
	message(STATUS "Add app ${app}")
	add_executable(${app} ${app}.cpp
		"${CMAKE_SOURCE_DIR}/thirdparty/glad/glad.c"
		${IMGUI_SRC}
	)
	target_compile_features(${app} PRIVATE cxx_std_17)
	#target_include_directories 针对项目， include_directoriees 针对全局
	# target_include_directories(${app} PRIVATE
	# 	"${CMAKE_SOURCE_DIR}/include"
	# 	# 使用源码导入
	# 	"${CMAKE_SOURCE_DIR}/thirdparty/glm"
	# 	"${CMAKE_SOURCE_DIR}/thirdparty/stb"
	# 	"${CMAKE_SOURCE_DIR}/thirdparty/imgui"
	# 	"${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends"
	# )
	target_link_libraries(${app} PRIVATE glfw modern_library)

	if(APPLE)
	    target_link_libraries(${app} PRIVATE "-framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon")
	endif()
endmacro()

# GLAPP(app)
# GLAPP(hello-triangle)
# GLAPP(shader)
# GLAPP(texture-demo)
# GLAPP(transformation)
# GLAPP(6.1.coordinate_systems)
# GLAPP(camera)
GLAPP(lighting)