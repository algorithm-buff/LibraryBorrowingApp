# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\LibraryBorrowingApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LibraryBorrowingApp_autogen.dir\\ParseCache.txt"
  "LibraryBorrowingApp_autogen"
  )
endif()
