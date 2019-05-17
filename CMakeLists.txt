cmake_minimum_required(VERSION 3.1)

project("Main")

set(PRODUCT main)
set(PRODUCT_SRC "src/main.cpp")
set(PRODUCT_ELF "${PRODUCT}.elf")
set(PRODUCT_HEX "${PRODUCT}.hex")

set(PARAM_MICROCONTROLLER "atmega328p")
set(PARAM_CPU_FREQUENCY "16000000")
set(PARAM_PROGRAMMER_TYPE "arduino")
set(PARAM_SERIAL_PORT "/dev/tty.usbserial-1420")
set(PARAM_SERIAL_BAUD_RATE "115200")
set(PARAM_MEMORY_TYPE "flash")
set(PARAM_MEMORY_MODE "w")
set(PARAM_MEMORY_OPERATION "${PARAM_MEMORY_TYPE}:${PARAM_MEMORY_MODE}:${PRODUCT_HEX}")

set(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_CXX_FLAGS "\
  -O \
  -mmcu=${PARAM_MICROCONTROLLER} \
  -DF_CPU=${PARAM_CPU_FREQUENCY} \
")

set(CMAKE_CXX_LINK_FLAGS "\
  -mmcu=${PARAM_MICROCONTROLLER} \
")

add_executable(${PRODUCT} ${PRODUCT_SRC})

set_target_properties(${PRODUCT} PROPERTIES OUTPUT_NAME ${PRODUCT_ELF})

add_custom_target(
  hex
  avr-objcopy
  --remove-section .eeprom
  --output-target ihex
  ${PRODUCT_ELF}
  ${PRODUCT_HEX}
)

add_custom_target(
  upload
  avrdude
  -F
  -V
  -c ${PARAM_PROGRAMMER_TYPE}
  -p ${PARAM_MICROCONTROLLER}
  -P ${PARAM_SERIAL_PORT}
  -b ${PARAM_SERIAL_BAUD_RATE}
  -U ${PARAM_MEMORY_OPERATION}
  DEPENDS hex
)
