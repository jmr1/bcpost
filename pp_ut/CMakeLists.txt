FIND_PACKAGE (GMock REQUIRED)

FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
LIST(REMOVE_ITEM test_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp ${CMAKE_CURRENT_SOURCE_DIR}/targetver.h ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
SET (test_LIBS ${LIBPARSER_NAME} ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
SET (test_BIN ${LIBPARSER_NAME_UT})
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})

include (CTest)
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
IF (project_build_shared)
  ADD_DEPENDENCIES(${test_BIN} ${LIBPARSER_NAME_SHARED})
ELSE (project_build_shared)
  ADD_DEPENDENCIES(${test_BIN} ${LIBPARSER_NAME_STATIC})
ENDIF (project_build_shared)
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})

IF (LEAKCHECK)
  SET (TEST_EXEC_CMD ${VALGRIND_PROGRAM} ${VALGRIND_CONFIG} --xml=yes --xml-file=${PROJECT_SOURCE_DIR}/output/${LIBPARSER_NAME}-ut-leakcheck.xml  ${MAINFOLDER}/bin/${test_BIN})
ELSE (LEAKCHECK)
  IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    SET (TEST_EXEC_CMD ${ENV} ${MAINFOLDER}/bin/${test_BIN})
  ELSE()
    SET (TEST_EXEC_CMD ${ENV} ${MAINFOLDER}/x64/Debug/${test_BIN})
  ENDIF()
ENDIF (LEAKCHECK)

IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  ADD_TEST(${LIBPARSER_NAME}-ut-test ${MAINFOLDER}/bin/${test_BIN})
ELSE()
  ADD_TEST(${LIBPARSER_NAME}-ut-test ${MAINFOLDER}/x64/Debug/${test_BIN})
ENDIF()
#ADD_CUSTOM_TARGET(${LIBPARSER_NAME}-test
#                    ${AUTORUN_TESTS}
#                    ${TEST_EXEC_CMD}
#                    DEPENDS ${test_BIN}
#                    WORKING_DIRECTORY "${MAINFOLDER}"
#                    COMMENT "Executing ${LIBPARSER_NAME}-test unit tests..."
#                    VERBATIM
#                    SOURCES ${test_SRCS})
