set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

message(${LIB_INCLUDE_DIR})

include_directories(${LIB_INCLUDE_DIR})
add_executable(Train Train.cpp)
target_link_libraries(Train rflib)

add_executable(Play Play.cpp)
target_link_libraries(Play rflib)

#INSTALL(TARGETS Train Play DESTINATION ${PROJECT_BIN_DIR}/bin)