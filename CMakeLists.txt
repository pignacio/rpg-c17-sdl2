cmake_minimum_required(VERSION 3.10)

project(Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(GCC_COVERAGE_COMPILE_FLAGS
    "-Werror -Wall -Wextra -Wconversion -Wshadow -fno-omit-frame-pointer -fsanitize=address"
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DCATCH_CONFIG_PREFIX_ALL)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(GTEST REQUIRED gtest>=-1.7.0)
find_package(GMOCK REQUIRED gmock>=1.7.0)

set(COMMON_SOURCES src/logging.h src/logging.cpp)
set(MAIN_SOURCES src/main.cpp)

add_executable(main ${MAIN_SOURCES} ${COMMON_SOURCES})

include_directories(
  src
  test
  ${SDL_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS})
include_directories(SYSTEM src/thirdparty)

target_link_libraries(main ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES})