file(GLOB FILELIST
main_core0.c
)

set(TARGET core0)
add_library(${TARGET} STATIC ${FILELIST})

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/driver/inc)
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/driver/inc/reg)
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/CMSIS/Core/Include/)
target_include_directories(${TARGET} PUBLIC ${BASE_DIR}/CMSIS/Device/RaspberryPi/RP2040/Include)
