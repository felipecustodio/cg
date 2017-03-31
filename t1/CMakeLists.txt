cmake_minimum_required(VERSION 2.8)
project(t1)

set(CMAKE_CXX_STANDARD 11)

include_directories(includes/
					src/
					)

file(GLOB INCS includes/*.h)
file(GLOB SRCS src/*.c)
source_group("Source" FILES ${SRCS})
source_group("Header" FILES ${INCS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lGLU -lglut")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL -lGLU -lglut")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(t1 ${SRCS} ${INCS})
target_link_libraries(t1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})