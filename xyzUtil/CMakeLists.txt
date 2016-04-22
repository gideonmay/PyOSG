ADD_LIBRARY(xyzUtil SHARED
        OffScreenRenderer.cpp
        OffScreenRendererPBuffer.cpp
        xyzUtil.cpp)

TARGET_LINK_LIBRARIES(xyzUtil ${OPENSCENEGRAPH_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

IF(NOT WIN32)
    # Kind of a hack but it works
        SET_TARGET_PROPERTIES(xyzUtil PROPERTIES PREFIX "_" SUFFIX ".so")
ELSE()
        SET_TARGET_PROPERTIES(xyzUtil PROPERTIES PREFIX "lib_" SUFFIX ".dll")
ENDIF()

#Find where to install Python libs
execute_process(COMMAND
                python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
                OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE
                )

INSTALL(TARGETS xyzUtil
        LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES}
        ARCHIVE DESTINATION ${PYTHON_SITE_PACKAGES}
       )
