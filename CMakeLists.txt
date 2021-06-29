cmake_minimum_required(VERSION 3.1)
project(externalTest)

set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

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