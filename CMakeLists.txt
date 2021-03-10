cmake_minimum_required(VERSION 3.14)
project(TradesKill C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories(/usr/include)

find_package(PkgConfig REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(Freetype CONFIG)

pkg_search_module(GLFW REQUIRED glfw3)

add_executable(TradesKill main.c globals.h keyboard.c keyboard.h window.c
        window.h timer.c timer.h state.c state.h mouse.c mouse.h linmath.h
        game.c game.h logger.h sprite.c sprite.h shader.c shader.h atlas.c
        atlas.h renderer.c renderer.h scene.c scene.h utils.c utils.h
        animation.c animation.h scenes/scene_primary.c scenes/scene_primary.h
        sprites/ore_gold.c sprites/ore_gold.h assets.h assets.c
        sprites/ore_copper.c sprites/ore_copper.h)

target_link_libraries(TradesKill GLEW::GLEW ${GLFW_STATIC_LIBRARIES}
        ${OPENGL_LIBRARIES} Freetype::Freetype pthread stb m)

add_custom_command(TARGET TradesKill PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_BINARY_DIR}/assets)

add_custom_command(TARGET TradesKill POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets)
