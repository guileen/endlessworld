macro(GLAPP app)
	message(STATUS "Add app ${app}")
	add_executable(${app} ${app}.cpp ../thirdparty/glad/glad.c)
	target_compile_features(${app} PRIVATE cxx_std_17)

	target_link_libraries(${app} PRIVATE glfw modern_library fmt::fmt)

	if(APPLE)
	    target_link_libraries(${app} PRIVATE "-framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon")
	endif()
endmacro()

GLAPP(app)
GLAPP(hello-triangle)
