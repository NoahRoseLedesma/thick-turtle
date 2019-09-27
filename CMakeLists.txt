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

aux_source_directory(include INCLUDE)
aux_source_directory(src SRC)

add_executable(thick-turtle
        ${INCLUDE}
        ${SRC}
        )

if(SFML_FOUND)
    include_directories("/usr/include")
    target_link_libraries(thick-turtle PUBLIC
            sfml-graphics
            sfml-window
            sfml-system)
endif()

target_compile_options(thick-turtle PRIVATE ${THICK-TURTLE_COMPILE_OPTIONS})
