cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(externalTest)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OpenGL_INCLUDE_DIR}")
find_package(X11 REQUIRED)
message(STATUS "Found X11 in ${X11_INCLUDE_DIR}")

#find_package(GLM REQUIRED)
#message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

add_definitions(${OPENGL_DEFINITIONS})


#find_package(ZLIB  QUIET) # even not found, cmake will not complain!!
#find_package(BZip2 QUIET) # even not found, cmake will not complain!!
#find_package(Threads REQUIRED) # launch usr/share/cmake/modules/FindThreads.cmake module to look for pthread.h
#find_package(DL      REQUIRED) # launch 3rd/FindDL.cmake module to look for posix dlopen function
#find_package(MySQL   REQUIRED) # launch 3rd/FindMySQL.cmake module, will fail this example
#find_package(OpenSSL REQUIRED) # launch usr/share/cmake/modules/FindOpenSSL.cmake module, will fail if no openssl-dev is installed

add_subdirectory(external/glm)
add_subdirectory(external/nvImage)
add_subdirectory(external/ode)
add_subdirectory(external/glfw)
add_subdirectory(external/vectorial)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTE_LIB	
	glm
	nvImage
	ode
	glfw
	vectorial
	pthread	
)
add_executable(execute main.cpp)
target_link_libraries(execute ${EXECUTE_LIB})