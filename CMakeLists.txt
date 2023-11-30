cmake_minimum_required(VERSION 3.10)

# set the project name
project(aoc_2023)

# uncomment to generate debug symbols
# set(CMAKE_BUILD_TYPE Debug)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# generate build_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(utils
        utils.cc
        )

add_subdirectory(test)

#############################
# per-day executables go here
#############################

#add_executable(day_xx
#        day_xx.cc
#        )
#target_link_libraries(day_xx
#        utils
#        )
