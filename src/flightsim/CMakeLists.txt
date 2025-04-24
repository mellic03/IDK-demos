cmake_minimum_required(VERSION 3.9)
project(FlightSim)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)


file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/character/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dev-ui/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game-ui/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/item/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world/world/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world/item/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world/weapon/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world/character/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/world/aircraft/*.cpp
)



add_executable(${PROJECT_NAME} ${SOURCES})

# set_target_properties(
#     ${PROJECT_NAME} PROPERTIES
#     POSITION_INDEPENDENT_CODE ON
# )


if (IDK_DEBUG)
    target_compile_options(${PROJECT_NAME} PUBLIC -Werror -fsanitize=undefined -lstdc++fs -g)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif ()


# add_library(${PROJECT_NAME} SHARED ${SOURCES})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)


include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})


target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    IDKBuiltinUI
    IDKGameEngine
)

