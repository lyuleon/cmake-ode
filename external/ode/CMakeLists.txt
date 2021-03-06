include(ExternalProject)

set(ODE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ODE_INSTALL_DIR ${CMAKE_BINARY_DIR}/lib/ode)
set(ODE_PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "ODE_SOURCE_DIR = ${ODE_SOURCE_DIR}")
message(STATUS "ODE_INSTALL_DIR = ${ODE_INSTALL_DIR}")
message(STATUS "ODE_PREFIX_DIR = ${ODE_PREFIX_DIR}")

set(ODE_CONFIGURE    cd ${ODE_PREFIX_DIR} && ${ODE_SOURCE_DIR}/configure --prefix=${ODE_INSTALL_DIR} --disable-demos)
set(ODE_MAKE         cd ${ODE_PREFIX_DIR} && make)
set(ODE_INSTALL      cd ${ODE_PREFIX_DIR} && make install)

ExternalProject_Add(libode	
	SOURCE_DIR	  ${ODE_SOURCE_DIR}
	INSTALL_DIR  	  ${ODE_INSTALL_DIR}
        PREFIX            ${ODE_PREFIX_DIR}
        CONFIGURE_COMMAND ${ODE_CONFIGURE}
        BUILD_COMMAND     ${ODE_MAKE}
        INSTALL_COMMAND   ${ODE_INSTALL}
)

# 指定编译好的静态库文件的路径
set(ODE_LIB       ${ODE_INSTALL_DIR}/lib/libode.a CACHE INTERNAL "ODE_LIB")
# 指定头文件所在的目录
set(ODE_INCLUDE_DIR ${ODE_INSTALL_DIR}/include CACHE INTERNAL "ODE_INCLUDE_DIR")

add_library(ode STATIC IMPORTED GLOBAL)

set_target_properties(ode PROPERTIES IMPORTED_LOCATION ${ODE_LIB})
set_target_properties(ode PROPERTIES INCLUDE_DIRECTORIES ${ODE_INCLUDE_DIR})
