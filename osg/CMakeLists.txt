SET(TARGET_SRC
        osg.cpp
        buildinfo.cpp
        Referenced.cpp
        Object.cpp
        Node.cpp
        BoundingBox.cpp
        BoundingSphere.cpp
        Vec2.cpp
        Vec3.cpp
        Vec3d.cpp
        Vec4.cpp
        Math.cpp
        Matrix.cpp
        Matrix2.cpp
        Camera.cpp
        View.cpp
        Timer.cpp
        CopyOp.cpp
        ApplicationUsage.cpp
        ArgumentParser.cpp
        Notify.cpp
        NodeVisitor.cpp
        NodeCallback.cpp
        FrameStamp.cpp
        Geode.cpp
        Transform.cpp
        Group.cpp
        Array.cpp
        ArrayByte.cpp
        ArrayFloat.cpp
        ArrayInt.cpp
        ArrayShort.cpp
        ArrayUByte.cpp
        ArrayUInt.cpp
        ArrayUShort.cpp
        ArrayVec2.cpp
        ArrayVec3.cpp
        ArrayVec4.cpp
        Quat.cpp
        StateAttribute.cpp
        Viewport.cpp
        ColorMask.cpp
        LightModel.cpp
        Light.cpp
        Material.cpp)

ADD_LIBRARY(osg SHARED ${TARGET_SRC})
TARGET_LINK_LIBRARIES(osg ${OPENSCENEGRAPH_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

IF(NOT WIN32)
    # Kind of a hack but it works
    SET_TARGET_PROPERTIES(osg PROPERTIES PREFIX "_" SUFFIX ".so")
ELSE()
    SET_TARGET_PROPERTIES(osg PROPERTIES PREFIX "lib_" SUFFIX ".dll")
ENDIF()

#Find where to install Python libs
execute_process ( COMMAND 
        python -c "from distutils.sysconfig import get_python_lib; print( get_python_lib())" 
                  OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)

INSTALL(TARGETS osg
        LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES}
        ARCHIVE DESTINATION ${PYTHON_SITE_PACKAGES}
       )
