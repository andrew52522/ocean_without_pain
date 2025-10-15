cmake_minimum_required(VERSION 3.14)
project(OceanSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Developer! Change the path to the SFML library here in set() at the bottom.
set(SFML_DIR "C:/Users/User/Documents/SFML-2.6.1/lib/cmake/SFML")

# Find the SFML package
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Automatically find all .cpp source files in the src folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create an executable from all found source files
add_executable(ocean_simulation ${SOURCES})

# 2. CONNECT THE LIBRARIES! This is the most important part.
target_link_libraries(ocean_simulation PRIVATE sfml-graphics)
