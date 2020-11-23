#
# Copyright (c) 2016-2020 Jean Davy
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

#
# Copyright (c) 2016-2020 Jean Davy
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Generate stage:
#   $mkdir build; cd build; cmake ..
#   Re-generate after changes:
#     $cmake .
#   Show each build command line as it is launched
#   $cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..
#   Generate a release version: $cmake -DCMAKE_BUILD_TYPE=Release ..

# Build stage:
#   Linux: $cmake --build . -- -j
#   Windows: $cmake --build . -- /maxcpucount
#   Build only test/action_defer:
#   $cmake --build . --target actions_defer

# Test stage:
#    Launch all tests: $ctest --verbose
#    To run tests with memcheck: $ctest -T memcheck
#    List available test: $ctest -N
#    Launch benchmark tests: $ctest -R benchmark*

cmake_minimum_required(VERSION 3.5)
project(robot_center LANGUAGES CXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 6.0.0)
  message(FATAL_ERROR "sml requires GCC >= 6.0.0")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 3.5.0)
  message(FATAL_ERROR "sml requires Clang >= 3.5.0")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
  message(FATAL_ERROR "sml requires Visual Studio 14 2015 at least")
endif()

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAS_CXX14_FLAG)
check_cxx_compiler_flag(-std=c++17 HAS_CXX17_FLAG)
check_cxx_compiler_flag(-std=c++2a HAS_CXX20_FLAG)

if(HAS_CXX20_FLAG)
  set(CMAKE_CXX_STANDARD 14)
elseif(HAS_CXX17_FLAG)
  set(CMAKE_CXX_STANDARD 14)
elseif(HAS_CXX14_FLAG)
  set(CMAKE_CXX_STANDARD 14)
else()
  message(FATAL_ERROR "sml requires c++14")
endif()

message(WARNING "Using CXX: " ${CMAKE_CXX_STANDARD})
if(NOT (DEFINED CMAKE_CXX_STANDARD) OR CMAKE_CXX_STANDARD STREQUAL "" OR CMAKE_CXX_STANDARD LESS 14)
    message(FATAL_ERROR "sml requires c++14")
endif()

set(IS_COMPILER_GCC_LIKE FALSE)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )

  set(IS_COMPILER_GCC_LIKE TRUE)
endif()

set(CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(cxxopts REQUIRED)
find_package(g3log CONFIG REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

message(
"g3log package:
    found: ${G3LOG_FOUND}
    include dir: ${G3LOG_INCLUDE_DIRS}
    libraries: ${G3LOG_LIBRARIES}
    "
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${G3LOG_INCLUDE_DIRS}
    ${LIBMONGOCXX_INCLUDE_DIRS}
    ${LIBBSONCXX_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    src/robot_center/robot_center.cpp
    src/sm/state_init.cpp src/sm/state_idle.cpp src/sm/state_error.cpp src/sm/state_map.cpp src/sm/state_mission.cpp src/sm/state_prep.cpp src/sm/sm.cpp
    src/helpers/fs_helper.cpp src/helpers/mongo_helper.cpp src/helpers/rabbit_helper.cpp src/helpers/ros_helper.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${LIBMONGOCXX_LIBRARIES}
    ${G3LOG_LIBRARIES}
    ${LIBBSONCXX_LIBRARIES}
    ${G3LOG_LIBRARIES}
    uv
    )
