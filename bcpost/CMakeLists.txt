FILE (GLOB_RECURSE bcpost_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
LIST(REMOVE_ITEM bcpost_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.cpp ${CMAKE_CURRENT_SOURCE_DIR}/targetver.h ${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h)
SET (bcpost_LIBS ${LIBPARSER_NAME} ${Boost_LIBRARIES})
SET (bcpost_BIN ${BCPOST_NAME})

ADD_EXECUTABLE(${bcpost_BIN} ${bcpost_SRCS})
IF (project_build_shared)
  ADD_DEPENDENCIES(${bcpost_BIN} ${LIBPARSER_NAME_SHARED})
ELSE (project_build_shared)
  ADD_DEPENDENCIES(${bcpost_BIN} ${LIBPARSER_NAME_STATIC})
ENDIF (project_build_shared)
TARGET_LINK_LIBRARIES(${bcpost_BIN} ${bcpost_LIBS})

IF (LEAKCHECK)
  SET (TEST_EXEC_CMD ${VALGRIND_PROGRAM} ${VALGRIND_CONFIG} --xml=yes --xml-file=${PROJECT_SOURCE_DIR}/output/${LIBPARSER_NAME}-leakcheck.xml  ${MAINFOLDER}/bin/${bcpost_BIN})
ELSE (LEAKCHECK)
  SET (TEST_EXEC_CMD ${ENV} ${MAINFOLDER}/bin/${bcpost_BIN})
ENDIF (LEAKCHECK)

