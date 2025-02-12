cmake_minimum_required(VERSION 3.10)
project(maestro)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    .
    ./cost-model/include
    ./cost-model/include/base
    ./cost-model/include/tools
    ./cost-model/include/user-api
    ./cost-model/include/dataflow-analysis
    ./cost-model/include/dataflow-specification-language
    ./cost-model/include/design-space-exploration
    ./cost-model/include/cost-analysis
    ./cost-model/include/abstract-hardware-model
    ./cost-model/src
)

find_package(Boost REQUIRED COMPONENTS program_options filesystem system)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
message(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Generate a CompilationDatabase (compile_commands.json file) for our build,
# for use by clang_complete, YouCompleteMe, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message(STATUS "CMake compile commands has been exported.")

add_executable(maestro
    maestro-top.cpp
    cost-model/src/BASE_base-objects.cpp
    cost-model/src/utils.cpp
)

target_link_libraries(maestro
    Boost::program_options
    Boost::filesystem
    Boost::system
)
