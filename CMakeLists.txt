cmake_minimum_required(VERSION 3.4)
project(main)

#add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(Core)
#add_subdirectory(ImageLoader)
# Find GLFW package
find_package(glfw3 3.3 REQUIRED)
add_executable(main main3.cpp)
target_link_libraries(main PUBLIC  glad glfw Shader TextureLoader)

target_include_directories(main PUBLIC 
                "${project_binary_dir}"
                "${project_source_dir}/glad")
                   
# specify the c++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

