cmake_minimum_required(VERSION 3.29)
project(learn_open_gl)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

# Add module files to a file set of type CXX_MODULES
target_sources(
        ${PROJECT_NAME}
        PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES samples/hallo_window.ixx  # Your C++20 module files
)

# Include FetchContent module to download dependencies from GitHub
include(FetchContent)

# Download and include GLFW (for windowing and input)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.8  # Use a specific version tag
)
FetchContent_MakeAvailable(glfw)

# Download and include GLAD (for OpenGL function loading)
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        v0.1.34
)
FetchContent_MakeAvailable(glad)

# Link GLFW and GLAD to the project
target_link_libraries(${PROJECT_NAME} glfw glad)

# Include GLAD headers
target_include_directories(${PROJECT_NAME} PRIVATE ${glad_SOURCE_DIR}/include)

# Platform-specific settings
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
elseif (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
