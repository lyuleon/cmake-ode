set(LIBHELLO_SRC 
	nvImage.cpp
	nvImageDDS.cpp
	nvImageHdr.cpp
	nvImagePng.cpp
	rgbe.c
)

add_library(nvImage STATIC ${LIBHELLO_SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/nvImage)