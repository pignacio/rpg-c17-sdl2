cmake_minimum_required(VERSION 3.10)

project(Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(GCC_COVERAGE_COMPILE_FLAGS
    "-Werror -Wall -Wextra -Wconversion -Wshadow -fno-omit-frame-pointer -fsanitize=address -fcolor-diagnostics"
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-DCATCH_CONFIG_PREFIX_ALL)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(GTEST REQUIRED gtest>=-1.7.0)
find_package(GMOCK REQUIRED gmock>=1.7.0)

set(COMMON_SOURCES
    src/data/map.cpp
    src/data/map.h
    src/data/table.h
    src/enum_array.h
    src/event/mouse.cpp
    src/event/mouse.h
    src/gfx/sprite_sheet.cpp
    src/gfx/sprite_sheet.h
    src/logging.cpp
    src/logging.h
    src/sdl/event.cpp
    src/sdl/event.h
    src/sdl/helpers.cpp
    src/sdl/helpers.h
    src/sdl/keyboard_state.cpp
    src/sdl/keyboard_state.h
    src/sdl/loader.cpp
    src/sdl/loader.h
    src/sdl/ptr.h
    src/sdl/renderer.cpp
    src/sdl/renderer.h
    src/sdl/surface.cpp
    src/sdl/surface.h
    src/sdl/texture.cpp
    src/sdl/texture.h
    src/sdl/window.cpp
    src/sdl/window.h
    src/utils/assert.cpp
    src/utils/assert.h
)

set(MAIN_SOURCES)

add_executable(main ${MAIN_SOURCES} ${COMMON_SOURCES})
target_sources(main PUBLIC src/main.cpp)

include_directories(
  src
  test
  ${SDL_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS}
)
include_directories(SYSTEM thirdparty)

target_link_libraries(
  main ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
)

add_executable(
  tests
  ${COMMON_SOURCES}
  ${MAIN_SOURCES}
  test/gfx/test_sprite_sheet.cpp
  test/mock_clock.cpp
  test/mock_clock.h
  test/point/test_point.cpp
  test/prelude.h
  test/sdl/mock_texture.cpp
  test/sdl/mock_texture.h
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
target_link_libraries(tests -O0 -fprofile-arcs -ftest-coverage
                      -DDISABLE_BACKTRACES)
