cmake_minimum_required(VERSION 3.0.0)
project(project4 VERSION 0.1.0)

include(CTest)
enable_testing()

# compile flags: -Wall "enable all compiler warnings"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# c++ language version level: c++11
set(CMAKE_CXX_STANDARD 11)

add_executable(a.out main.cc parser.cc lexer.cc inputbuf.cc token.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
