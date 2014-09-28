CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(BoostEx C CXX)

# Variables
SET(DEBUG_FLAGS "-ggdb -Wall -Wextra -Winline -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_REENTRANT ${DEBUG_FLAGS}")
SET(BOOST_ROOT  "${CMAKE_SOURCE_DIR}/libs")
SET(GTEST_ROOT  "${BOOST_ROOT}")
SET(BOOST_EXE "BoostTest")
SET(PY_LIB   "Boost")

FIND_PACKAGE(Boost 1.56.0 REQUIRED chrono date_time filesystem
    program_options python system thread)
FIND_PACKAGE(GTest 1.7 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(PythonLibs 2 REQUIRED)

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(progOpts)
ADD_SUBDIRECTORY(python)

OPTION(ProgOpts "ProgOpts" OFF)
OPTION(Python "Python" OFF)
OPTION(Test "Test" OFF)

IF(Test)
    ADD_EXECUTABLE(${BOOST_EXE} ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES(${BOOST_EXE}
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_BOTH_LIBRARIES}
    )
ENDIF(Test)

IF(ProgOpts)
    ADD_EXECUTABLE(ProgOpts1 ${PO_1_SOURCES})
    ADD_EXECUTABLE(ProgOpts2 ${PO_2_SOURCES})
    ADD_EXECUTABLE(ProgOpts3 ${PO_3_SOURCES})
    TARGET_LINK_LIBRARIES(ProgOpts1
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_BOTH_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(ProgOpts2
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_BOTH_LIBRARIES}
    )
    TARGET_LINK_LIBRARIES(ProgOpts3
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${GTEST_BOTH_LIBRARIES}
    )
ENDIF(ProgOpts)

IF(Python)
    ADD_LIBRARY(
        ${PY_LIB}
        SHARED
        ${PY_LIB_SOURCES}
        ${PY_LIB_HEADERS}
    )
    TARGET_LINK_LIBRARIES(${PY_LIB}
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${PYTHON_LIBRARIES}
    )
    ADD_CUSTOM_COMMAND(
        TARGET ${PY_LIB} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/libBoost.so ${CMAKE_SOURCE_DIR}/python
    )
ENDIF(Python)

# Debug
#GET_CMAKE_PROPERTY(_variablenames variables)
#FOREACH (_variablename ${_variablenames})
    #MESSAGE(STATUS "${_variableName}=${${_variableName}}")
#ENDFOREACH(_variablename)
