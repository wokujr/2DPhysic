cmake_minimum_required(VERSION 3.28)

project(2DGamePhysic
    VERSION 1.0.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include SDL2 headers
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/header"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Set the path to SDL2 libraries
set(SDL2_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x64")

# Use FetchContent to download and include SDL2_gfx
include(FetchContent)                                           # Include the FetchContent module to manage dependencies

FetchContent_Declare(
    SDL2_gfx
    GIT_REPOSITORY https://github.com/ferzkopp/SDL2_gfx.git     # Repository for SDL2_gfx
    GIT_TAG main                                                # Select the main branch, perhaps?
    #GIT_TAG release-2.26.3                                     #-> IDK but it cannot be can... :( 
)

FetchContent_MakeAvailable(SDL2_gfx)                            # Fetch and make SDL2_gfx available

# Add the SDL2_gfx library
# Link SDL2_gfx directly since it doesn't use CMake
add_library(SDL2_gfx STATIC
    ${sdl2_gfx_SOURCE_DIR}/SDL2_gfxPrimitives.c
    ${sdl2_gfx_SOURCE_DIR}/SDL2_framerate.c
    ${sdl2_gfx_SOURCE_DIR}/SDL2_imageFilter.c
    ${sdl2_gfx_SOURCE_DIR}/SDL2_rotozoom.c
)

# Define the executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Include the SDL2_gfx headers
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_gfx_SOURCE_DIR}                                      # Include SDL2_gfx headers directory
)

# Link against SDL2 and SDL2_gfx libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    "${SDL2_LIB_DIR}/SDL2.lib"                                  # Link SDL2 library
    "${SDL2_LIB_DIR}/SDL2main.lib"                              # Link SDL2main library
    SDL2_gfx                                                    # Link SDL2_gfx library
)

# Custom function for copying libraries (optional)
function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

# Copy SDL2.dll to the target directory (if needed)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL2_LIB_DIR}/SDL2.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/config.h" ESCAPE_QUOTES
)

# Specify source files for the project
target_sources(${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/vec2.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vec2.cpp"
	
    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/application.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/application.cpp"
	
    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/graphics.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/graphics.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/particles.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/particles.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/header/constants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/constants.cpp"
)




# was About to use this but i'm stupid then download it manually, add it to repo directly haha.... :( sorry im stupid, maybe im not fit to be a programmer
# SDL2 (assuming you already have SDL2 integrated)
# FetchContent_Declare(
#   SDL2
#   GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#   GIT_TAG release-2.26.3
# )
# FetchContent_MakeAvailable(SDL2)