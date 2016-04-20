ADD_LIBRARY(osgGA SHARED
        osgGA.cpp
        GUIEventHandler.cpp
        )

TARGET_LINK_LIBRARIES(osgGA ${OPENSCENEGRAPH_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

IF(NOT WIN32)
    # Kind of a hack but it works
        SET_TARGET_PROPERTIES(osgGA PROPERTIES PREFIX "_" SUFFIX ".so")
ELSE()
        SET_TARGET_PROPERTIES(osgGA PROPERTIES PREFIX "lib_" SUFFIX ".dll")
ENDIF()

#Find where to install Python libs
execute_process( COMMAND
                python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
                OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE
)

INSTALL(TARGETS osgGA
        LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES}/PyOSG
        ARCHIVE DESTINATION ${PYTHON_SITE_PACKAGES}/PyOSG
)
