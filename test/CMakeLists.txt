include_directories($<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)

add_executable(test-output output.cpp)
target_link_libraries(test-output ${PROJECT_NAME})
add_test(NAME output
  COMMAND $<TARGET_FILE:test-output>
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
