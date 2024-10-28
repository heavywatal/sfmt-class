cmake_minimum_required(VERSION 3.15)
project(sfmt
  VERSION 0.7.6
  LANGUAGES C CXX)

cmake_policy(SET CMP0169 OLD) # 3.28
set(CMAKE_VERBOSE_MAKEFILE ON)
include(CMakePrintHelpers)
include(FetchContent)
include(GNUInstallDirs)
cmake_print_variables(CMAKE_INSTALL_PREFIX)

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
FetchContent_GetProperties(CSFMT)
if(NOT csfmt_POPULATED)
  FetchContent_Populate(CSFMT)
endif()
cmake_print_variables(csfmt_SOURCE_DIR)

set(MEXP 19937)
set(csfmt_srcs
  ${csfmt_SOURCE_DIR}/SFMT.h
  ${csfmt_SOURCE_DIR}/SFMT-params.h
  ${csfmt_SOURCE_DIR}/SFMT-params${MEXP}.h
)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/include/SFMT)
foreach(src IN LISTS csfmt_srcs)
  cmake_print_variables(src)
  configure_file(${src} ${PROJECT_SOURCE_DIR}/include/SFMT COPYONLY)
endforeach()

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
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-config
)
install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

set(config_destination ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}-config
  DESTINATION ${config_destination}
  NAMESPACE wtl::
)

set(version_file ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${version_file}
  COMPATIBILITY AnyNewerVersion
)
install(FILES ${version_file}
  DESTINATION ${config_destination}
)

include(CTest)
if(BUILD_TESTING AND ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  add_subdirectory(test)
endif()
