cmake_minimum_required(VERSION 3.1)
project(sfmt C CXX)

include(GNUInstallDirs)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_definitions(-DNDEBUG)
add_compile_options(-O3 -march=native -Wall -Wextra -Wpedantic)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)  # before add_definitions()
endif()

set(MEXP 19937)
add_definitions(-DHAVE_SSE2 -DSFMT_MEXP=${MEXP})
set(source_files SFMT/SFMT.c)

message("CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

add_library(${PROJECT_NAME} SHARED ${source_files})
add_library(${PROJECT_NAME}-static STATIC ${source_files})
set_target_properties(${PROJECT_NAME}-static PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static
  EXPORT ${PROJECT_NAME}-config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES sfmt.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES SFMT/SFMT.h SFMT/SFMT-params.h SFMT/SFMT-params${MEXP}.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SFMT
)
install(EXPORT ${PROJECT_NAME}-config
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
)
