cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(externalTest)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(ZLIB  QUIET) # even not found, cmake will not complain!!
find_package(BZip2 QUIET) # even not found, cmake will not complain!!

find_package(Threads REQUIRED) # launch usr/share/cmake/modules/FindThreads.cmake module to look for pthread.h
find_package(DL      REQUIRED) # launch 3rd/FindDL.cmake module to look for posix dlopen function
#find_package(MySQL   REQUIRED) # launch 3rd/FindMySQL.cmake module, will fail this example
#find_package(OpenSSL REQUIRED) # launch usr/share/cmake/modules/FindOpenSSL.cmake module, will fail if no openssl-dev is installed

add_subdirectory(external/nvImage)
add_subdirectory(external/ode)
add_subdirectory(external/glfw)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(execute main.cpp)

#message(STATUS "ODE_LIB = ${ODE_LIB}")
#message(STATUS "ODE_INCLUDE_DIR = ${ODE_INCLUDE_DIR}")

#target_link_libraries(execute ${ODE_LIB})
#target_include_directories(execute PRIVATE ${ODE_INCLUDE_DIR})

target_link_libraries(execute ode pthread glfw)