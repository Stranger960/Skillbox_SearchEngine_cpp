cmake_minimum_required(VERSION 3.8)

project(server_test)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.10.5
        )
FetchContent_MakeAvailable(json)

add_executable(${PROJECT_NAME} index_tests.cpp server_tests.cpp gen_test.cpp
    ${CMAKE_SOURCE_DIR}/src/invertedIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/converterJSON.cpp
    ${CMAKE_SOURCE_DIR}/src/searchServer.cpp)


gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC ${gtest_SOURCE_DIR}/include ${INCLUDE_DIR})
