cmake_minimum_required(VERSION 3.15)
project(exercises)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../googletest googletest)

add_executable(exercises)
target_include_directories(exercises PRIVATE src/_test_setup)
target_sources(exercises PRIVATE
    src/_test_setup/test_setup.cpp
    src/bus_stops/app.h
    src/bus_stops/app.cpp
    src/bus_stops/tests.cpp
#    src/bus_stops_2/app.cpp
#    src/bus_stops_2/tests.cpp
#    src/capital_cities/app.cpp
#    src/capital_cities/tests.cpp
#    src/names/app.cpp
#    src/names/tests.cpp
#    src/sorted/app.cpp
#    src/sorted/tests.cpp
#    src/synonims/app.cpp
#    src/synonims/tests.cpp
)

target_link_libraries(exercises gtest_main)

# treat warnings as errors
target_compile_options(exercises PRIVATE -Wall -Wextra -pedantic -Werror)