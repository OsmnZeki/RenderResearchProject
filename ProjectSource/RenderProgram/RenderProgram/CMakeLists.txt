get_source(RDRP_SOURCE_FILES RDRP_HEADER_FILES)

SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMake")

get_property(GLFW GLOBAL PROPERTY GLFW)
get_property(GLSRC GLOBAL PROPERTY GLSRC)
get_property(STB GLOBAL PROPERTY STB)

#file( GLOB_RECURSE glsl "[^.]*.glsl")

ADD_LIBRARY(RenderProgram STATIC ${RDRP_SOURCE_FILES} ${RDRP_HEADER_FILES} ${GLSRC} ${STB})                # ${glsl})

include_directories("${CMAKE_SOURCE_DIR}/OpenGL/include")
include_directories(include)

TARGET_LINK_LIBRARIES(RenderProgram ${GLFW} ${GLM_LIBRARIES})