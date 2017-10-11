cmake_minimum_required(VERSION 3.0)

project (XOX)
set(CMAKE_BUILD_TYPE Release)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")

find_package(Boost COMPONENTS system filesystem serialization REQUIRED)

file( GLOB LIB_SOURCES "lib/*.cpp" )
file( GLOB LIB_HEADERS "lib/*.h" )
set (PROJECT_DIR )
set ( LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib")
link_libraries( ${Boost_LIBRARIES} )

include_directories(${Boost_INCLUDE_DIR})
include_directories(${LIB_INCLUDE_DIR})

add_library( rflib ${LIB_SOURCES} ${LIB_HEADERS} )
link_directories(${Boost_LIBRARY_DIR})

add_subdirectory(src)
add_subdirectory(test) 

enable_testing()
add_test (MainTest test/MainTest)
