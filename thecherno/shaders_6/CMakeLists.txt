# amazingly, this seems to work
# was expecting GLEW to be capitalized
# while glfw in lower case
# can see that when had the error that
# couldn't find either glewConfig.cmake or glew-config.cmake
# but there was a GLEWConfig.cmake
cmake_minimum_required(VERSION 2.8)

set (OpenGL_GL_PREFERENCE "GLVND")
project(shaders_6)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL)

add_executable(${PROJECT_NAME} "main.cpp")
# add_executable has to come before target_link_libraries
target_link_libraries(shaders_6 OpenGL glfw GLEW)
