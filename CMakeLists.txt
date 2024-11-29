cmake_minimum_required(VERSION 3.22.0)

project("eos-name-converter")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${CONVERTER_SOURCES} main.cpp)

if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(external/googletest)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

    add_executable(converter-test ${TEST_SOURCES} ${CONVERTER_SOURCES})
    target_link_libraries(converter-test PRIVATE gtest_main)

    include(GoogleTest)
    gtest_discover_tests(converter-test)
endif()
