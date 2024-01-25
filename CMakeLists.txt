cmake_minimum_required(VERSION 3.26)
project(RaytrcerNJ_gl LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/glm")

link_directories("${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS on)

aux_source_directory(./src DIR_ALL_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${DIR_ALL_SRC})

target_link_libraries(${PROJECT_NAME} "libassimp-5.dll" "libglfw3.a" "libassimp.dll.a")
