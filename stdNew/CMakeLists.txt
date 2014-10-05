SET(STD_SOURCES
    ${STD_SOURCES}
    "${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/threads_create_test.cpp"
    #"${CMAKE_CURRENT_SOURCE_DIR}/threads_mutex_test.cpp"
    PARENT_SCOPE
)

SET(STD_HEADERS
    ${STD_HEADERS}
    "${CMAKE_CURRENT_SOURCE_DIR}/util.hpp"
    PARENT_SCOPE)
