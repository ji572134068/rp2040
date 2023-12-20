set(CMSIS_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMSIS_VENDOR RaspberryPi)
set(CMSIS_DEVICE RP2040)

add_library(cmsis INTERFACE)
target_sources(cmsis INTERFACE
        ${CMSIS_PATH}/Device/${CMSIS_VENDOR}/${CMSIS_DEVICE}/Source/system_${CMSIS_DEVICE}.c
)
target_include_directories(cmsis INTERFACE
        ${CMSIS_PATH}/Core/Include
        ${CMSIS_PATH}/Device/${CMSIS_VENDOR}/${CMSIS_DEVICE}/Include
)
target_link_libraries(cmsis INTERFACE driver)