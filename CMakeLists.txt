cmake_minimum_required(VERSION 3.15...3.18)

# Set up our project
project(
  threadbare
  VERSION 0.1.0
  DESCRIPTION "Practising multi-threading"
  HOMEPAGE_URL "https://github.com/rufus-stone/threadbare"
  LANGUAGES CXX)

# Create our executable
add_executable(${PROJECT_NAME} src/main.cpp src/job.cpp)

# We're using C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set some compiler options/warnings
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra
                                               -Wold-style-cast -Wpedantic)

# Conan scripts
include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)

# Pull in the conan dependencies
conan_cmake_run(REQUIRES spdlog/1.8.2 BASIC_SETUP CMAKE_TARGETS BUILD missing)

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link libraries to executable
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::spdlog)
