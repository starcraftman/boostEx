SET(TEST_SOURCES
    ${TEST_SOURCES}
    #"${CMAKE_CURRENT_SOURCE_DIR}/gtest_example_primer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp"
    #"${CMAKE_CURRENT_SOURCE_DIR}/circle_buffer_test.cpp"
    #"${CMAKE_CURRENT_SOURCE_DIR}/date_time_test.cpp"
    #"${CMAKE_CURRENT_SOURCE_DIR}/filesystem_test.cpp"
    #"${CMAKE_CURRENT_SOURCE_DIR}/foreach_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/threads_test.cpp"
    PARENT_SCOPE
)

SET(TEST_HEADERS
    ${TEST_HEADERS}
    PARENT_SCOPE
)
