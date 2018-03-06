cmake_minimum_required(VERSION 3.9)
project(attic C)
set(PROJECT_NAME attic)

set(CMAKE_C_STANDARD 11)
set(INCLUDE_DIR src src/commands)

include_directories(/usr/local/include /usr/local/lib)

add_executable(${PROJECT_NAME} main.c src/utils.c src/utils.h src/config.c src/config.h src/commands/install.c src/commands/install.h src/commands/uninstall.c src/commands/uninstall.h src/commands/setup.c src/commands/setup.h src/commands/help.c src/commands/help.h src/commands/list.c src/commands/list.h src/color.h src/verbose.c src/verbose.h src/commands/commands.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
