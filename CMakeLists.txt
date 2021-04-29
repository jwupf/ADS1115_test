cmake_minimum_required(VERSION 3.16)

project(ads1115)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ADS1115Support)

add_executable(ads1115 main.cpp)

target_link_libraries(ads1115 PUBLIC ADS1115Support)

target_include_directories(ads1115 PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_SOURCE_DIR}/ADS1115Support"
                        )
