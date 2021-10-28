SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMake")

find_package(OpenGL REQUIRED)

include_directories(include)
link_directories(lib)

file( GLOB_RECURSE include "[^.]*.h" "[^.]*.hpp")
file( GLOB_RECURSE sources "[^.]*.c")

set(GLFW ${OPENGL_gl_LIBRARY} ${CMAKE_SOURCE_DIR}/OpenGL/lib/glfw3.lib)
set(GLSRC ${CMAKE_CURRENT_SOURCE_DIR}/sources/glad.c)
set(STB ${CMAKE_CURRENT_SOURCE_DIR}/include/STB/stb.cpp)

set_property(GLOBAL PROPERTY GLFW "${GLFW}")
set_property(GLOBAL PROPERTY GLSRC "${GLSRC}")
set_property(GLOBAL PROPERTY STB "${STB}")