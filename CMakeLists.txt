cmake_minimum_required(VERSION 3.15)
project(learn_cpp)

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

add_executable(
        learn_cpp
        main.cpp
)

include_directories(include)
add_executable(
        capital_cities
        apps/capital_cities/app.cpp
        apps/capital_cities/tests.cpp)
target_link_libraries(capital_cities gtest_main)

add_executable(
        bus_stops_2
        apps/bus_stops_2/app.cpp
        apps/bus_stops_2/tests.cpp
)
target_link_libraries(bus_stops_2 gtest_main)

add_executable(
        synonims
        apps/synonims/app.cpp
        apps/synonims/tests.cpp
)
target_link_libraries(synonims gtest_main)
enable_testing()