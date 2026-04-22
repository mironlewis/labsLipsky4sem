cmake_minimum_required(VERSION 3.15)
project(Lab2UITesting)

set(CMAKE_CXX_STANDARD 17)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

set(CURL_DISABLE_TESTS ON CACHE INTERNAL "")
set(BUILD_CURL_EXE OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(HTTP_ONLY ON CACHE INTERNAL "")
set(CURL_USE_SCHANNEL ON CACHE INTERNAL "")

FetchContent_Declare(
        curl
        URL https://github.com/curl/curl/releases/download/curl-8_7_1/curl-8.7.1.zip
)
FetchContent_MakeAvailable(curl)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_executable(
        Lab2UITesting
        lab2UITests/main.cpp
        tests/UITests.cpp
        tests/NavigationTests.cpp
        tests/ProductTests.cpp
)

target_link_libraries(
        Lab2UITesting
        gtest
        gtest_main
        libcurl
)

include(GoogleTest)
gtest_discover_tests(Lab2UITesting)