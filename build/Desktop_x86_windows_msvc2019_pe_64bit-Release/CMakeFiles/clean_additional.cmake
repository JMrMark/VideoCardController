# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\VideoCardControl_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VideoCardControl_autogen.dir\\ParseCache.txt"
  "VideoCardControl_autogen"
  )
endif()
