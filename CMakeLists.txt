cmake_minimum_required(VERSION 3.16)

project(ads1115)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build stuff(build the executable)

add_subdirectory(src)

add_executable(ads1115 main.cpp)

target_link_libraries(ads1115 PUBLIC ADS1115Support)
target_link_libraries(ads1115 PUBLIC logger)

target_include_directories(ads1115 PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        "${PROJECT_SOURCE_DIR}/src/ADS1115Support"
                        "${PROJECT_SOURCE_DIR}/src/logger"
                        )

# Test stuff(prep, configure, build the tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

add_subdirectory(test)
