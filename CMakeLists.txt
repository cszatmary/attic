cmake_minimum_required(VERSION 3.9)
project(attic C)
set(PROJECT_NAME attic)

set(CMAKE_C_STANDARD 11)

set(INCLUDE_DIR src src/commands)

add_executable(${PROJECT_NAME} main.c src/utils.c src/utils.h src/config.c src/config.h src/commands/install.c src/commands/install.h src/commands/uninstall.c src/commands/uninstall.h src/commands/setup.c src/commands/setup.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} config)