cmake_minimum_required(VERSION 3.10)
set(PROJ_NAME "app")
set(BIN_FILE ${PROJ_NAME}.bin)
set(ASM_FILE ${PROJ_NAME}.asm)
project(${PROJ_NAME} VERSION 0.1)

# toolchain path
set(TOOLCHAIN "arm-none-eabi-")
set(CMAKE_C_COMPILER "${TOOLCHAIN}gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN}gcc")
set(CMAKE_OBJCOPY "${TOOLCHAIN}objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN}objdump")
set(CMAKE_AR "${TOOLCHAIN}ar")
set(CMAKE_RANLIB "${TOOLCHAIN}ranlib")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/ram.ld")

set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR})

set(MCU_FLAGS "-mcpu=cortex-m0plus -mthumb -g -O2 -Wall -nostartfiles -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS "${MCU_FLAGS}")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,-Map=app.map")

enable_language(ASM)
add_executable(${PROJ_NAME}.elf main.c)
target_sources(${PROJ_NAME}.elf PUBLIC start.S)

add_subdirectory(${BASE_DIR}/driver driver)
target_link_libraries(${PROJ_NAME}.elf driver)

add_subdirectory(${BASE_DIR}/CMSIS)
target_link_libraries(${PROJ_NAME}.elf cmsis)

add_subdirectory(${BASE_DIR}/core0)
target_link_libraries(${PROJ_NAME}.elf core0)

add_subdirectory(${BASE_DIR}/core1)
target_link_libraries(${PROJ_NAME}.elf core1)

add_custom_command(TARGET ${PROJ_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJ_NAME}.elf> ${BIN_FILE}
    COMMAND ${CMAKE_OBJDUMP} -d -S $<TARGET_FILE:${PROJ_NAME}.elf> >${ASM_FILE}
    COMMENT "Generate ${BIN_FILE}\r\n"
)
