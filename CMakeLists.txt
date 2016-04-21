CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "RELEASE")
    #SET(CMAKE_BUILD_TYPE "DEBUG")
    #SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
    #SET(CMAKE_BUILD_TYPE "MINSIZEREL")
ENDIF()

set ( CMAKE_CXX_FLAGS "-Wno-#pragma-messages -Wno-potentially-evaluated-expression")

PROJECT( PyOSG )


FIND_PROGRAM(PYTHON "python")

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
FIND_PACKAGE(OpenSceneGraph 3.4 REQUIRED osgDB osgUtil osgGA osgViewer osgSim)
FIND_PACKAGE(Boost 1.45.0 REQUIRED)
FIND_PACKAGE(OpenGL)

IF(Boost_FOUND)
      INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}")
      SET(Boost_USE_STATIC_LIBS OFF)
      SET(Boost_USE_MULTITHREADED ON)
      SET(Boost_USE_STATIC_RUNTIME OFF)
      # FIND_PACKAGE(Boost 1.45.0 COMPONENTS python3)
      FIND_PACKAGE(Boost 1.45.0 COMPONENTS python)

      # ADD_LIBRARY(yay SHARED yay.cxx)
ELSEIF(NOT Boost_FOUND)
    MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

# ENABLE_TESTING()
INCLUDE_DIRECTORIES(include ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${OPENSCENEGRAPH_INCLUDE_DIRS})
# LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

ADD_SUBDIRECTORY(animate)
ADD_SUBDIRECTORY(testviewer)

ADD_SUBDIRECTORY(osg)
ADD_SUBDIRECTORY(osgDB)
ADD_SUBDIRECTORY(osgUtil)
ADD_SUBDIRECTORY(osgGA)
ADD_SUBDIRECTORY(osgViewer)

ADD_SUBDIRECTORY(xyzUtil)

IF(PYTHON)
        SET (SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
        SET (SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
        SET (DEPS        "${CMAKE_CURRENT_SOURCE_DIR}/PyOSG/__init__.py")
        SET (OUTPUT      "${CMAKE_CURRENT_BINARY_DIR}/build")
        configure_file(${SETUP_PY_IN} ${SETUP_PY})

       add_custom_command(
           OUTPUT ${OUTPUT}/timestamp
           COMMAND ${PYTHON} setup.py build
           COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}/timestamp
           DEPENDS ${DEPS}
        )
    add_custom_target(target ALL DEPENDS ${OUTPUT}/timestamp)
    install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")
ENDIF()

add_custom_target(install_${PROJECT_NAME}
        make install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")
