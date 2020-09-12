cmake_minimum_required(VERSION 3.0.0)
project(utf8 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(
  "."
)
add_library(utf8 utf8.c)

add_executable(utf8_example_file examples/utf8_example_file.c)
target_link_libraries(utf8_example_file utf8)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
