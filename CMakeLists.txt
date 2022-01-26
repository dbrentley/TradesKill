cmake_minimum_required(VERSION 3.14)
project(TradesKill C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -DGLEW_STATIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGLEW_STATIC")

include_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

link_directories("${PROJECT_SOURCE_DIR}/lib")

set(GLEW_ROOT "${PROJECT_SOURCE_DIR}/lib")

find_package(OpenGL REQUIRED)

add_executable(TradesKill ${RES_FILES} glew.c main.c globals.h keyboard.c
               keyboard.h window.c window.h timer.c timer.h state.c state.h
               mouse.c mouse.h linmath.h game.c game.h sprite.c sprite.h
               shader.c shader.h atlas.c atlas.h renderer.c renderer.h utils.c
               utils.h animation.c animation.h sprites/ore_gold.h assets.h
               assets.c sprites/ore_copper.h queue.h queue.c
               sprites/effect_bling.h libmtwist/mt.c libmtwist/mtwist.h
               libmtwist/mtwist_internal.h libmtwist/seed.c sprites/common.c
               sprites/common.h sprites/hero.h sprites/grass.h
               libmtwist/mtwist.h stb_image.h sprites/ore.h sprites/tree.h
               system.c system.h tskmath.h)

target_link_libraries(TradesKill glu32 glew32.dll ${OPENGL_LIBRARIES} glfw3 m)

set(RES_FILES "")
if (MINGW)
    set(RES_FILES "assets/TradesKill.rc")
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
        "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif (MINGW)

add_custom_command(TARGET TradesKill PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E remove_directory
                   ${CMAKE_BINARY_DIR}/assets)

add_custom_command(TARGET TradesKill POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets
                   ${CMAKE_BINARY_DIR}/assets)

add_custom_command(TARGET TradesKill PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E remove_directory
                   ${CMAKE_BINARY_DIR}/assets)

add_custom_command(TARGET TradesKill POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets
                   ${CMAKE_BINARY_DIR}/assets)
