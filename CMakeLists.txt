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

# Link against SDL2 libraries
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    "${SDL2_LIB_DIR}/SDL2.lib"
    "${SDL2_LIB_DIR}/SDL2main.lib"
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
)