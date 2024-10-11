cmake_minimum_required(VERSION 3.10)

# Project name
project(cppgpt_example)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add cpr and nlohmann_json as dependencies
include(FetchContent)

if(NOT TARGET cpr)
    FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                            GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
    FetchContent_MakeAvailable(cpr)
endif()

if(NOT TARGET nlohmann_json)
FetchContent_Declare(nlohmann_json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(nlohmann_json)
endif()

# Executables
add_executable(cppgpt_example main.cpp)
add_executable(cppgroq_example groq.cpp)

# Link libraries
target_link_libraries(cppgpt_example PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
target_link_libraries(cppgroq_example PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
