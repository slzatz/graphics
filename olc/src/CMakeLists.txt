# This is the CMakeLists.txt for compiling listmanager_term_improved.cpp
# with QT Creator.
# The output executable is listmanager_term_improved_qtc and I moved it from
# the build directory to ~/c_stuff/listmanager

cmake_minimum_required(VERSION 3.15)

project(oclPixelGameEngine)
set(ExecutableName test) 

set (OpenGL_GL_PREFERENCE "GLVND")

set(SourceDir src)
set(THREADS_PREFER_PTHREAD_FLAD ON)

find_package(X11 REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${PNG_INCLUDE_DIR})

set(Executable ${ExecutableName}.o)
# these 3 lines were from thecherno for his example helloworld
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wsign-compare -std=c++2a")
#set (source_dir "${PROJECT_SOURCE_DIR}/")

# the below obviously shouldn't be a GLOB since only one source file
#file (GLOB source_files "${source_dir}/listmanager_term_improved.*")

#add_subdirectory("${source_dir}/tests") #new
add_executable(${Executable} ${SourceDir}/olcengine3d_obj.cpp)

# note that for what we're doing doesn't matter whether PUBLIC or PRIVATE (see CMAKE docs)
target_include_directories(${Executable} PUBLIC "${source_dir}")
# add_executable has to come before target_link_libraries

# case is important and tripped me up below related to SQLITE and POSTGRES
target_link_libraries(${Executable} Threads::Threads OpenGL::OpenGL OpenGL::GL OpenGL::GLX ${X11_LIBRARIES} PNG::PNG)

