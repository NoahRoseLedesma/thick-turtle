cmake_minimum_required(VERSION 3.13)
project(thick-turtle)

set(THICK-TURTLE_COMPILE_OPTIONS -Wall -Werror)

include_directories(./include ./src)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

find_package(SFML 2 COMPONENTS
        system
        window
        graphics
        network
        audio
        REQUIRED)

add_executable(thick-turtle
        include/map.h
        include/piece.h
        include/player.h
        include/tile.h
        include/utility.h
        include/game.h
        include/camera.h
        include/inputcontroller.h

        src/map.cc
        src/piece.cc
        src/player.cc
        src/tile.cc
        src/utility.cc
        src/game.cc
        src/camera.cc
        src/inputcontroller.cc

        src/main.cc
        src/minesweepertile.cc include/minesweepertile.h src/minesweepertile.cc include/minesweepertile.h)

if(SFML_FOUND)
    include_directories("/usr/include")
    target_link_libraries(thick-turtle PUBLIC
            sfml-graphics
            sfml-window
            sfml-system)
endif()

target_compile_options(thick-turtle PRIVATE ${THICK-TURTLE_COMPILE_OPTIONS})
