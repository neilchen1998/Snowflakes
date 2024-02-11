# cmake requirements
cmake_minimum_required(VERSION 3.14)

project(
    Snowflakes
    VERSION 0.1
    DESCRIPTION "Generates beautiful snowflakes"
    LANGUAGES CXX
)

# checks if we are in the main CMakeLists
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # ensures -std=c++xx instead of -std=g++xx for protability purposes
    set(CMAKE_CXX_EXTENSIONS OFF)

    # add profiling flags (gprof)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

    # compiler flags
    add_compile_options(-Wall -Wextra -pedantic -O3 -pg)

    # uses CTest
    # NOTE: this needs to be done in the main CMakeLists
    include(CTest)

    # Docs only available in the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found")
    endif()
endif()

# FetchContent helps grabbing repos during the configure step
# NOTE: available after CMake 3.11
include(FetchContent)

# all required packages
find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED) # boost::program_options

# the compiled library code
add_subdirectory(src)

# the executable code
add_subdirectory(apps)

# checks if we are in the main CMakeLists
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()
