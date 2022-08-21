cmake_minimum_required(VERSION 3.0.0)
project(project4 VERSION 0.1.0)

include(CTest)
enable_testing()

# compile flags: -Wall "enable all compiler warnings"
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# c++ language version level: c++11
set(CMAKE_CXX_STANDARD 11)

# Uncomment the version of project to build
set(    ThisProject 
        #"project1"
        #"project2"
        #"project3"
        "project4"
    )
# Add the project specific include path
include_directories(${PROJECT_SOURCE_DIR}/${ThisProject})

# define a.out as being composed of these source files
add_executable( a.out
                main.cc 
                parser.cc 
                lexer.cc 
                inputbuf.cc 
                ${ThisProject}/token.cc 
                execute.cc)

# Xcode specific compiler settings
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options(a.out PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()

# Ubuntu (Linux) specific compile settings
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    target_compile_options(a.out PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
endif()

# Microsoft specific compile settings
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options(a.out PRIVATE /Wall /wd4820 /wd4514 /D__STDC_WANT_SECURE_LIB__=1)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
