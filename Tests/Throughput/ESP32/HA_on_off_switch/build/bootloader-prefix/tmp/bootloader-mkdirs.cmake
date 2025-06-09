# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP-IDF/components/bootloader/subproject"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/tmp"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/src/bootloader-stamp"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/src"
  "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "H:/STM32WB5MM-DK Project/zigbee-playground/Tests/Throughput/ESP32/HA_on_off_switch/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
