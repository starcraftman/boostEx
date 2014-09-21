SET(TEST_SOURCES
    ${TEST_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/gtest_example_primer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_foreach.cpp"
    PARENT_SCOPE
)

SET(TEST_HEADERS
    ${TEST_HEADERS}
    PARENT_SCOPE
)
