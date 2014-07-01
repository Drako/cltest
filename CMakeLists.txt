PROJECT ( CLTest )
CMAKE_MINIMUM_REQUIRED ( VERSION 3.0.0 )

# for g++ and clang++
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.0")
        SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
    ELSE ()
        SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    ENDIF ()
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # will have to adjust this... older clang versions may need -std=c++0x
    # but I could not find an exact version number :-/
    SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ENDIF ()

SET ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

FIND_PACKAGE ( OpenCL REQUIRED )

FILE ( GLOB clt_SOURCES *.cxx )
FILE ( GLOB clt_HEADERS *.hxx )

INCLUDE_DIRECTORIES ( ${OPENCL_INCLUDE_DIR} )

ADD_EXECUTABLE ( CLTest ${clt_SOURCES} ${clt_HEADERS} )
TARGET_LINK_LIBRARIES ( CLTest ${OPENCL_LIBRARY} )

