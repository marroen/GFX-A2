# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

# Define the project name and version
project(project VERSION 1.0 LANGUAGES CXX)

# Define the C++ standard and other options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the 'include' folder to the search path
include_directories(${PROJECT_SOURCE_DIR}/include/project)

# Add a subdirectory for third-party libraries (like LLGL)
add_subdirectory(third_party/LLGL)
add_subdirectory(third_party/glm)

# Define the source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link LLGL (or other libraries) to the project
target_link_libraries(${PROJECT_NAME} LLGL)
target_link_libraries(${PROJECT_NAME} glm)

