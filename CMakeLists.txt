cmake_minimum_required(VERSION 3.1)
project(sfmt C CXX)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(MEXP 19937)
add_definitions(-DNDEBUG -DHAVE_SSE2 -DSFMT_MEXP=${MEXP} -DDSFMT_MEXP=${MEXP})
set(CMAKE_C_FLAGS "-O3 -msse2 -Wall -Wextra -fno-strict-aliasing")

set(source_files SFMT/SFMT.c dSFMT/dSFMT.c)

add_library(${PROJECT_NAME} SHARED ${source_files})
add_library(${PROJECT_NAME}-static STATIC ${source_files})
set_target_properties(${PROJECT_NAME}-static PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "~/local" CACHE PATH "install prefix" FORCE)
endif()
message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static
  EXPORT ${PROJECT_NAME}-config
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
install(FILES sfmt.hpp
  DESTINATION include
)
install(FILES SFMT/SFMT.h SFMT/SFMT-params.h SFMT/SFMT-params${MEXP}.h
  DESTINATION include/SFMT
)
install(FILES dSFMT/dSFMT.h
  DESTINATION include/dSFMT
)
install(EXPORT ${PROJECT_NAME}-config
  DESTINATION share/${PROJECT_NAME}
)
