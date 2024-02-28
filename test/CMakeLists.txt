link_libraries(wtl::${PROJECT_NAME})

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
  get_filename_component(name_we ${src} NAME_WE)
  add_executable(test-${name_we} ${src})
  add_test(NAME ${name_we}
    COMMAND $<TARGET_FILE:test-${name_we}>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )
endforeach()
