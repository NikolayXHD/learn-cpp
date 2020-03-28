cmake_minimum_required(VERSION 3.15)
project(exercises)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL
        )

include_directories(src/_test_setup)
add_executable(exercises)
target_sources(exercises PRIVATE
    src/_test_setup/test_setup.cpp
    src/bus_stops/app.cpp
    src/bus_stops/tests.cpp
    src/bus_stops_2/app.cpp
    src/bus_stops_2/tests.cpp
    src/capital_cities/app.cpp
    src/capital_cities/tests.cpp
    src/names/app.cpp
    src/names/tests.cpp
    src/sorted/app.cpp
    src/sorted/tests.cpp
    src/synonims/app.cpp
    src/synonims/tests.cpp
)

target_link_libraries(exercises gtest_main)
enable_testing()
