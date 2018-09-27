link_libraries(wtl::${PROJECT_NAME})

add_executable(test-output output.cpp)
add_test(NAME output
  COMMAND $<TARGET_FILE:test-output>
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(test-example example.cpp)
add_test(NAME example COMMAND $<TARGET_FILE:test-example>)
