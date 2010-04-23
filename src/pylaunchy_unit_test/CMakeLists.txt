CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(FindGoogleTest)
FIND_PACKAGE(Qt4 REQUIRED) # find and setup Qt3 for this project
FIND_PACKAGE(GoogleTest REQUIRED)
INCLUDE(${QT_USE_FILE}) 

INCLUDE_DIRECTORIES("../ezlogger") 
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_LIBRARIES(${PYTHON_LIBRARIES})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
LINK_LIBRARIES(${GTEST_LIBRARIES})

INCLUDE_DIRECTORIES("../pylaunchy")


SET(PyLaunchyTest_SRCS
	ScriptsDirectoryConfigTest.cpp
	ScriptPluginWrapperTest.cpp
)

SET(PyLaunchyTest_ARGS --gtest_print_time )

IF(WANT_TEST)
	message(${CMAKE_CTEST_COMMAND})
	FOREACH(testSrc ${PyLaunchyTest_SRCS})
		GET_FILENAME_COMPONENT(TestName ${testSrc} NAME_WE)
		ADD_EXECUTABLE( ${TestName} main.cpp ${testSrc} )
		TARGET_LINK_LIBRARIES(${TestName} ${QT_LIBRARIES})
		TARGET_LINK_LIBRARIES(${TestName} PyLaunchyStaticLib)
		ADD_TEST( ${TestName} ${TestName} ${PyLaunchyTest_ARGS} )
	ENDFOREACH(testSrc ${tests_SRCS})
ENDIF(WANT_TEST)

