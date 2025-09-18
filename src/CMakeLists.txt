cmake_minimum_required(VERSION 3.8)

project(search_engine)

# get JSON from github
include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.10.5
        )
FetchContent_MakeAvailable(json)

add_executable(${PROJECT_NAME} Search_engine.cpp "../include/searchEngine.h" ${INCLUDE_DIR}/converterJSON.h converterJSON.cpp
     invertedIndex.cpp ${INCLUDE_DIR}/invertedIndex.h ${INCLUDE_DIR}/searchServer.h searchServer.cpp )

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/config/requests.json ${CMAKE_CURRENT_BINARY_DIR})
