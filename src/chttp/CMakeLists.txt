include_directories("./")
include_directories("../../3dparty/glob")

FILE(GLOB_RECURSE CHTTP_SRC_FILES *.c)
add_library(chttp STATIC ${CHTTP_SRC_FILES})
target_link_libraries(chttp glob)