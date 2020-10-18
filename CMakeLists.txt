cmake_minimum_required(VERSION 3.9)
project(attic C)
set(PROJECT_NAME attic)

set(CMAKE_C_STANDARD 99)
set(INCLUDE_DIR src third_party)

# include_directories(/usr/local/include /usr/local/lib)

add_executable(${PROJECT_NAME}
    src/cmd/cmd.c
    src/cmd/cmd.h
    src/cmd/config.c
    src/cmd/install.c
    src/cmd/list.c
    src/cmd/reinstall.c
    src/cmd/uninstall.c
    src/color.h
    src/config.c
    src/config.h
    src/error.h
    src/main.c
    src/util.c
    src/util.h
    src/verbose.c
    src/verbose.h
    third_party/cJSON/cJSON.c
    third_party/cJSON/cJSON.h
    third_party/sds/sds.c
    third_party/sds/sds.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wstrict-prototypes)
