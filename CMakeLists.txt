cmake_minimum_required(VERSION 3.7)

project(GUI)

# Include dear imgui
file(GLOB IMGUI_SRC
     "${PROJECT_SOURCE_DIR}/lib/imgui-1.52/*.cpp"
)
include_directories("${PROJECT_SOURCE_DIR}/lib/imgui-1.52")

# Set up graphics stuff
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS})

# Main GUI source files
file(GLOB GUI_SRC
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/*.h"
)

# Main GUI executable
add_executable(gui ${IMGUI_SRC} ${GUI_SRC})

# Link
target_link_libraries(gui ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glfw ${SDL2_LIBRARIES})
