file(GLOB FILELIST
src/common.c
src/system.c
src/reset.c
src/clock.c
src/sio.c
src/gpio.c
)

set(TARGET driver)
add_library(${TARGET} STATIC ${FILELIST})

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/reg)
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/CMSIS/Core/Include/)
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/CMSIS/Device/RaspberryPi/RP2040/Include)
