cmake_minimum_required(VERSION 3.15)
project(sfmt
  VERSION 0.7.5
  LANGUAGES C CXX)

cmake_policy(SET CMP0076 NEW)
set(CMAKE_VERBOSE_MAKEFILE ON)
include(CMakePrintHelpers)
include(FetchContent)
include(GNUInstallDirs)
cmake_print_variables(CMAKE_INSTALL_PREFIX)
if(${CMAKE_INSTALL_PREFIX} MATCHES linuxbrew)
  set(CMAKE_INSTALL_LIBDIR lib)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
cmake_print_variables(CMAKE_BUILD_TYPE)
set(CMAKE_C_FLAGS_DEV "-O2 -g")
set(CMAKE_CXX_FLAGS_DEV "-O2 -g")

function(import_env variable)
  if(DEFINED ENV{${variable}})
    set(${variable} $ENV{${variable}} PARENT_SCOPE)
  endif()
endfunction()

import_env("FETCHCONTENT_SOURCE_DIR_CSFMT")
cmake_print_variables(FETCHCONTENT_SOURCE_DIR_CSFMT)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
  CSFMT
  GIT_REPOSITORY https://github.com/heavywatal/SFMT.git
  GIT_TAG init64
  GIT_SHALLOW ON
  SOURCE_DIR _deps/SFMT
)
FetchContent_Populate(CSFMT)
cmake_print_variables(csfmt_SOURCE_DIR)

set(MEXP 19937)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
add_library(${PROJECT_NAME} ${csfmt_SOURCE_DIR}/SFMT.c)
add_library(wtl::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -pedantic
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},x86_64>:-march=native>
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},arm64>:-march=armv8.3-a+sha3>
)
target_compile_definitions(${PROJECT_NAME} PUBLIC
  -DSFMT_MEXP=${MEXP}
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},x86_64>:-DHAVE_SSE2>
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},arm64>:-DHAVE_NEON -DHAVE_SHA3>
)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${csfmt_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES sfmt.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES
  ${csfmt_SOURCE_DIR}/SFMT.h
  ${csfmt_SOURCE_DIR}/SFMT-params.h
  ${csfmt_SOURCE_DIR}/SFMT-params${MEXP}.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SFMT
)
install(EXPORT ${PROJECT_NAME}-config
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  NAMESPACE wtl::
)

set(VERSION_CONFIG ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${VERSION_CONFIG} COMPATIBILITY AnyNewerVersion
)
install(FILES ${VERSION_CONFIG}
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
)

include(CTest)
if(BUILD_TESTING AND ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  add_subdirectory(test)
endif()
