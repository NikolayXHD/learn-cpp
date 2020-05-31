cmake_minimum_required(VERSION 3.15)
project(app)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        app
        main.cpp
)

# treat warnings as errors
target_compile_options(app PRIVATE -Wall -Wextra -pedantic -Werror)
