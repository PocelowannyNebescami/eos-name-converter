cmake_minimum_required(VERSION 3.22.0)

project("eos-name-converter")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${CONVERTER_SOURCES} main.cpp)
