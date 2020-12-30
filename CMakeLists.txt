cmake_minimum_required(VERSION 3.15...3.18)

# Set up our project
project(
  my_proj
  VERSION 0.1.0
  DESCRIPTION "Fill me in"
  HOMEPAGE_URL "Fill me in"
  LANGUAGES CXX)

# Create our executable
add_executable(${PROJECT_NAME} src/main.cpp)

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

include(CTest) # This adds the BUILD_TESTING option (ON by default)
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
