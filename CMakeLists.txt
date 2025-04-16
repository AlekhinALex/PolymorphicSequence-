cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "inc/*.hpp")
file(GLOB IMPLEMENTATIONS "impl/*.tpp")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} inc impl)

add_executable(lab2
    src/main.cpp
    ${HEADERS}
    ${IMPLEMENTATIONS}
)

# add_executable(googleTests
#     tests/googleTests.cpp
#     ${HEADERS}
#     ${IMPLEMENTATIONS}
# )

# target_link_libraries(googleTests GTest::GTest GTest::Main pthread)
