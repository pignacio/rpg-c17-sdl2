cmake_minimum_required(VERSION 3.10)

project(Test)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(GCC_COVERAGE_COMPILE_FLAGS
    "-Werror -Wall -Wextra -Wconversion -Wshadow -fno-omit-frame-pointer -fsanitize=address -fcolor-diagnostics"
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DCATCH_CONFIG_PREFIX_ALL)

MESSAGE(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(GTEST REQUIRED gtest>=-1.7.0)
find_package(GMOCK REQUIRED gmock>=1.7.0)

set(COMMON_SOURCES
    src/data/map.cpp
    src/data/map.hpp
    src/data/table.hpp
    src/direction.cpp
    src/direction.hpp
    src/enum_array.hpp
    src/event/mouse.cpp
    src/event/mouse.hpp
    src/gfx/actor_animation.cpp
    src/gfx/actor_animation.hpp
    src/gfx/sprite_sheet.cpp
    src/gfx/sprite_sheet.hpp
    src/logging.cpp
    src/logging.hpp
    src/sdl/event.cpp
    src/sdl/event.hpp
    src/sdl/helpers.cpp
    src/sdl/helpers.hpp
    src/sdl/keyboard_state.cpp
    src/sdl/keyboard_state.hpp
    src/sdl/loader.cpp
    src/sdl/loader.hpp
    src/sdl/ptr.hpp
    src/sdl/renderer.cpp
    src/sdl/renderer.hpp
    src/sdl/surface.cpp
    src/sdl/surface.hpp
    src/sdl/texture.cpp
    src/sdl/texture.hpp
    src/sdl/window.cpp
    src/sdl/window.hpp
    src/serialization/serialization.hpp
    src/serialization/result.hpp
    src/utils/assert.cpp
    src/utils/assert.hpp
    src/utils/strings.cpp
    src/utils/strings.hpp
)

add_library(common ${COMMON_SOURCES})

set(MAIN_SOURCES)
set(EDITOR_SOURCES)

add_executable(main ${MAIN_SOURCES})
target_sources(main PUBLIC src/main.cpp)
target_link_libraries(
  main ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${CONAN_LIBS} common
)

add_executable(editor ${EDITOR_SOURCES})
target_sources(editor PUBLIC src/main_editor.cpp)
target_link_libraries(
  editor ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${CONAN_LIBS} common
)

include_directories(
  src
  test
  ${SDL_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS}
  ${CONAN_INCLUDE_DIRS}
)
include_directories(SYSTEM thirdparty)

MESSAGE(STATUS "Conan include: ${CONAN_INCLUDE_DIRS}, libs: ${CONAN_LIBS}")

add_executable(
  tests
  ${COMMON_SOURCES}
  ${MAIN_SOURCES}
  test/gfx/test_sprite_sheet.cpp
  test/mock_clock.cpp
  test/mock_clock.hpp
  test/point/test_point.cpp
  test/prelude.hpp
  test/sdl/mock_texture.cpp
  test/sdl/mock_texture.hpp
  test/sdl/test_event.cpp
  test/sdl/test_keyboard_state.cpp
  test/sdl/test_renderer.cpp
  test/test_logging.cpp
  test/test_mock_clock.cpp
  test/test_main.cpp)

target_link_libraries(
  tests ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
  ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})

target_compile_options(tests PUBLIC -O0 -fprofile-arcs -ftest-coverage
                                    -DDISABLE_BACKTRACES)
target_link_libraries(tests -fprofile-arcs -ftest-coverage
                                    -DDISABLE_BACKTRACES)
