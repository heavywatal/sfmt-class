configure_file(
  ${csfmt_SOURCE_DIR}/SFMT.19937.out.txt
  ${PROJECT_BINARY_DIR}/SFMT/SFMT.19937.out.txt COPYONLY
)
configure_file(
  ${csfmt_SOURCE_DIR}/SFMT.19937.64.out.txt
  ${PROJECT_BINARY_DIR}/SFMT/SFMT.19937.64.out.txt COPYONLY
)

file(GLOB srcfiles *.cpp)
foreach(src IN LISTS srcfiles)
  cmake_path(GET src STEM name_we)
  add_executable(test-${name_we} ${src})
  target_link_libraries(test-${name_we} wtl::${PROJECT_NAME})
  add_test(NAME ${name_we}
    COMMAND $<TARGET_FILE:test-${name_we}>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )
endforeach()
