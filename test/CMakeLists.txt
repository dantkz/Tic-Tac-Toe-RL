set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${LIB_INCLUDE_DIR})

link_directories(${Boost_LIBRARY_DIR})

add_executable(MainTest MainTest.cpp)
target_link_libraries(MainTest reinforcelib ${Boost_LIBRARIES})

