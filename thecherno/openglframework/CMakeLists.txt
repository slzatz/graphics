# amazingly, this seems to work
# was expecting GLEW to be capitalized
# while glfw in lower case
# can see that when had the error that
# couldn't find either glewConfig.cmake or glew-config.cmake
# but there was a GLEWConfig.cmake
cmake_minimum_required(VERSION 3.14)

project(thecherno)

set (OpenGL_GL_PREFERENCE "GLVND")

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL)

# these 3 lines were from thecherno for his example helloworld
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
# was c++14
#set (source_dir "${PROJECT_SOURCE_DIR}/")
set (source_dir "${PROJECT_SOURCE_DIR}/OpenGL/src")
#file (GLOB source_files "${source_dir}/*.cpp", "${source_dir}/tests/*.cpp", "${source_dir}/vendor/imgui/*.cpp", "${source_dir}/vendor/stb_image/stb_image.cpp")
file (GLOB source_files "${source_dir}/*.cpp" "${source_dir}/vendor/imgui/*.cpp")

#add_subdirectory("${source_dir}/tests") #new
#add_executable(${PROJECT_NAME} ${source_files})
add_executable(${PROJECT_NAME})
add_subdirectory("${source_dir}")
add_subdirectory("${source_dir}/vendor/imgui")
add_subdirectory("${source_dir}/vendor/stb_image")
add_subdirectory("${source_dir}/tests")
# note that GLM is only headers

# note that for what we're doing doesn't matter whether PUBLIC or PRIVATE (see CMAKE docs)
target_include_directories(thecherno PUBLIC "${source_dir}")
target_include_directories(thecherno PUBLIC "${source_dir}/tests")
target_include_directories(thecherno PUBLIC "${source_dir}/vendor/stb_image")
target_include_directories(thecherno PUBLIC "${source_dir}/vendor/glm")
target_include_directories(thecherno PUBLIC "${source_dir}/vendor/imgui")
# add_executable has to come before target_link_libraries
target_link_libraries(thecherno OpenGL glfw GLEW)

# Note that there is a CMakeLists.txt in:  src, src/vendor/imgui, src/vendor/stb_image and src/tests
# src CMakeLists.txt: target_sources(thecherno PRIVATE Application.cpp IndexBuffer.cpp Renderer.cpp Shader.cpp Texture.cpp VertexArray.cpp VertexBuffer.cpp)
# stb_image CMakeLists.txt: target_sources(thecherno PRIVATE stb_image.cpp)
# imgui CMakeLists.txt target_sources(thecherno PRIVATE imgui.cpp imgui_draw.cpp imgui_impl_glfw_gl3.cpp)
# tests CMakeLists.txt target_sources(thecherno PRIVATE Text.cpp TestClearColor.cpp TestTexture2d.cpp)
