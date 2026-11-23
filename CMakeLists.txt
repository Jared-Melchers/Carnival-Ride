cmake_minimum_required(VERSION 2.8...3.5)

project(Carnival_Ride)

# Executables
add_executable(CarnivalRide.out CarnivalRide.cpp 
               Objects/Objects.cpp Objects/ObjectTools
               Objects/Characters.cpp)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

# Linked files
target_link_libraries(CarnivalRide.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})