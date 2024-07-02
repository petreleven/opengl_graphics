add_library(Shader Shader.cpp)
add_library(TextureLoader TextureLoader.cpp)
target_include_directories(Shader PUBLIC "${CMAKE_CURRENT_DIR}")
target_include_directories(TextureLoader PUBLIC "${CMAKE_CURRENT_DIR}")

