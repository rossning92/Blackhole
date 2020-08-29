cmake_minimum_required(VERSION 2.7)


set(PROJECT_NAME main)

project(${PROJECT_NAME})

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/*.h"
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/*.c"
    "${PROJECT_SOURCE_DIR}/*.cc"
)

add_executable(main
    ${SRC_FILES}
)

target_link_libraries(main PRIVATE imgui::imgui)
target_link_libraries(main PRIVATE glfw)
target_link_libraries(main PRIVATE GLEW::GLEW)
target_link_libraries(main PRIVATE glm)
target_include_directories(main PRIVATE ${STB_INCLUDE_DIRS})
target_compile_features(main PRIVATE cxx_std_17)
