# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Admin/esp/v5.2.1/esp-idf/components/bootloader/subproject"
  "E:/ESP32/dcmm/micro_speech/build/bootloader"
  "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix"
  "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/tmp"
  "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/src/bootloader-stamp"
  "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/src"
  "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/ESP32/dcmm/micro_speech/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
