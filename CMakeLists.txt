#   Copyright 2024 hidenorly
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

cmake_minimum_required(VERSION 3.22)

# project config
project(SampleProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cxx)
set(MAIN_FILE ${SRC_DIR}/Sample.cxx)
list(REMOVE_ITEM SRC_FILES ${MAIN_FILE})

add_executable(sample ${MAIN_FILE} ${SRC_FILES})
target_include_directories(sample PRIVATE ${INCLUDE_DIR})
target_compile_options(sample PRIVATE -Wall -Wextra -Werror)

# google test
enable_testing()
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/test)
file(GLOB_RECURSE TEST_FILES ${TESTS_DIR}/*.cxx)
add_executable(test_MessageQueue ${TEST_FILES} ${SRC_FILES})
target_include_directories(test_MessageQueue PRIVATE ${INCLUDE_DIR})
find_package(GTest REQUIRED)
target_link_libraries(test_MessageQueue GTest::GTest GTest::Main)
add_test(NAME Tests COMMAND test_MessageQueue)
