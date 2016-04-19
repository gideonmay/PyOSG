// Copyright (C) 2002-2005 Gideon May (gideon@c1016.nl)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <string>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Version>
#include <osg/Image>

#include "held_ptr.hpp"

using namespace boost::python;

#ifndef VERSION
#  define VERSION  "3.0 alpha"
#endif

namespace PyOSG {
    void init_Object();
    void init_NodeVisitor();
    void init_Notify();
    void init_State();
    void init_FrameStamp();
    void init_BoundingBox();
    void init_BoundingSphere();
    void init_ClusterCullingCallback();
    void init_CoordinateSystemNode();
    void init_CullSettings();
    void init_CullStack();
    void init_CullingSet();
    void init_CopyOp();
    void init_BlendColor();
    void init_BlendEquation();
    void init_LogicOp();
    void init_FragmentProgram();
    void init_DisplaySettings();
    void init_Drawable();
    void init_Drawable2();
    void init_Drawable3();
    void init_Geometry();
    void init_DrawPixels();
    void init_Image();
    void init_ImageStream();
    void init_ApplicationUsage();
    void init_ArgumentParser();
    void init_Array();
    void init_ArrayByte();
    void init_ArrayShort();
    void init_ArrayInt();
    void init_ArrayUByte();
    void init_ArrayUShort();
    void init_ArrayUInt();
    void init_ArrayFloat();
    void init_ArrayUByte4();
    void init_ArrayVec2();
    void init_ArrayVec3();
    void init_ArrayVec4();
    void init_math();
    void init_Vec2();
    void init_Vec3();
    void init_Vec3d();
    void init_Vec4();
    void init_Quat();
    void init_UByte4();
    void init_Plane();
    void init_matrix();
    void init_Node();
    void init_NodeCallback();
    void init_Geode();
    void init_Billboard();
    void init_Group();
    void init_OccluderNode();
    void init_Sequence();
    void init_Switch();
    void init_Projection();
    void init_LOD();
    void init_ClearNode();
    void init_ClipNode();
    void init_Transform();
    void init_MatrixTransform();
    void init_DOFTransform();
    void init_PositionAttitudeTransform();
    void init_AutoTransform();
    void init_PrimitiveSet();
    void init_StateAttribute();
    void init_Material();
    void init_LineWidth();
    void init_LineSegment();
    void init_LineStipple();
    void init_ColorMask();
    void init_ColorMatrix();
    void init_ClipPlane();
    void init_Depth();
    void init_Stencil();
    void init_LightModel();
    void init_FrontFace();
    void init_TexGen();
    void init_TexMat();
    void init_VertexProgram();
    void init_AlphaFunc();
    void init_CullFace();
    void init_PolygonMode();
    void init_PolygonOffset();
    void init_PolygonStipple();
    void init_ShadeModel();
    void init_BlendFunc();
    void init_Fog();
    void init_Point();
    void init_TexEnv();
    void init_TexEnvCombine();
    void init_StateSet();
    void init_TexGenNode();
    void init_Texture();
    void init_Texture1D();
    void init_Texture2D();
    void init_Texture3D();
    void init_TextureCubeMap();
    void init_TextureRectangle();
    void init_Timer();
    void init_Light();
    void init_LightSource();
    void init_AnimationPath();
    void init_Viewport();
    void init_ConvexPlanarOccluder();
    void init_ConvexPlanarPolygon();
    void init_Shape();
    void init_ShapeDrawable();
    void init_TriangleFunctor();
    void init_Referenced();
    void init_CollectOccludersVisitor();
    void init_PointSprite();
    void init_CameraNode(); /* Deprecated */
    void init_Shader();
    void init_Program();

    const char * buildinfo();
}

using namespace PyOSG;

namespace {

typedef std::vector<osg::Group *> ParentList;

class Ref {
  public:
    Ref() {}
    Ref(osg::Referenced * obj) { _ref = obj; }
    osg::Referenced * get() { return _ref.get(); }
    void set(osg::Referenced * obj) { _ref = obj;}
    osg::Referenced * obj() {
        std::cerr << "Ref.obj : " << typeid(_ref.get()).name() << std::endl;
        return _ref.get();
    }

    ~Ref() {}
    osg::ref_ptr<osg::Referenced> _ref;
};

#define REF_COUNT 0

int aliveCount()
{
#if REF_COUNT
    return osg::Referenced::createdCount() - osg::Referenced::deletedCount();
#else
    return 0;
#endif
}

int createdCount()
{
#if REF_COUNT
    return osg::Referenced::createdCount();
#else
    return 0;
#endif
}

int deletedCount()
{
#if REF_COUNT
    return osg::Referenced::deletedCount();
#else
    return 0;
#endif
}

void __init_osg()
{
    // Some of the base classes are defined within this file, all the other
    // are defined within their own source files

    class_<Ref>("ref")
        .def(init<osg::Referenced *>())
        .def("get", &Ref::get,
            return_value_policy<manage_osg_object>())
        .def("set", &Ref::set)
        .def("__call__", &Ref::get,
            return_value_policy<manage_osg_object>())
        .def("obj", &Ref::obj,
            return_value_policy<manage_osg_object>())
        ;


    // The order of initialisation is important. Base
    // classes need to be initialized before derived
    // classes!

    init_Referenced();
    init_Object();
//    init_Timer();
//    init_CopyOp();
//    init_ApplicationUsage();
//    init_ArgumentParser();
//    init_Notify();
//    init_NodeVisitor();
//    init_NodeCallback();
//    init_FrameStamp();
//    init_BoundingBox();
//    init_BoundingSphere();
//    init_State();
//    init_CullSettings();
//    init_CullingSet();
//    init_CullStack();
//    init_DisplaySettings();
//    init_math();
//    init_Vec2();
//    init_Vec3();
//    init_Vec3d();
//    init_Vec4();
//    init_Quat();
//    init_UByte4();
//    init_Plane();
//    init_LineSegment();
//    init_Array();
//    init_ArrayByte();
//    init_ArrayShort();
//    init_ArrayInt();
//    init_ArrayUByte();
//    init_ArrayUShort();
//    init_ArrayUInt();
//    init_ArrayFloat();
//    init_ArrayUByte4();
//    init_ArrayVec2();
//    init_ArrayVec3();
//    init_ArrayVec4();
//    init_matrix();
//    init_Drawable();
//    init_Drawable2();
//    init_Drawable3();
//    init_Geometry();
//    init_DrawPixels();
//    init_Image();
//    init_ImageStream();
//    init_StateAttribute();
//    init_Material();
//    init_LineWidth();
//    init_LineStipple();
//    init_ColorMask();
//    init_ColorMatrix();
//    init_ClipPlane();
//    init_Depth();
//    init_Stencil();
//    init_LightModel();
//    init_FrontFace();
//    init_TexGen();
//    init_TexMat();
//    init_VertexProgram();
//    init_AlphaFunc();
//    init_CullFace();
//    init_PolygonMode();
//    init_PolygonOffset();
//    init_PolygonStipple();
//    init_ShadeModel();
//    init_BlendFunc();
//    init_Fog();
//    init_Point();
//    init_TexEnv();
//    init_TexEnvCombine();
//    init_StateSet();
//    init_Texture();
//    init_Texture1D();
//    init_Texture2D();
//    init_Texture3D();
//    init_TextureCubeMap();
//    init_TextureRectangle();
//    init_AnimationPath();
//    init_Viewport();
//    init_Light();
//    init_PrimitiveSet();
    init_Node();
//    init_Geode();
//    init_Billboard();
//    init_Group();
//    init_OccluderNode();
//    init_LOD();
//    init_TexGenNode();
//    init_Switch();
//    init_Projection();
//    init_ClearNode();
//    init_Sequence();
//    init_ClipNode();
//    init_Transform();
//    // init_CameraNode();
//    init_MatrixTransform();
//    init_PositionAttitudeTransform();
//    init_AutoTransform();
//    init_LightSource();
//    init_ConvexPlanarOccluder();
//    init_ConvexPlanarPolygon();
//    init_Shape();
//    init_ShapeDrawable();
//    init_BlendColor();
//    init_BlendEquation();
//    init_LogicOp();
//    init_FragmentProgram();
//    init_CollectOccludersVisitor();
//    init_ClusterCullingCallback();
//    init_CoordinateSystemNode();
//    init_PointSprite();
//    init_Shader();
//    init_Program();

    def("GetVersion",
        (const char *(*)()) &osgGetVersion,
        "GetVersion() returns the library version number.\n"
        "Numbering convention : OpenSceneGraph-0.8-31 will return 0.8.31 from GetVersion.\n"
        );

    def("GetLibraryName",
        (const char *(*)()) &osgGetLibraryName,
        "GetLibraryName() returns the library name in human friendly form.\n");

    def("createdCount", &createdCount);
    def("deletedCount", &deletedCount);
    def("aliveCount", &aliveCount);
}
}// namespace

BOOST_PYTHON_MODULE(_osg)
{
    // std::cerr << "BOOST_PYTHON_MODULE(osg)\n";
    // std::cerr << "Build = " << buildinfo() << std::endl;

    // Setup the osg module info
    scope().attr("__doc__") = "Wrapper for the OpenSceneGraph core scene graph library\n";
    scope().attr("__name__") = "PyOSG.osg";
#ifdef NDEBUG
    scope().attr("__version__") =  VERSION " release";
#else
    scope().attr("__version__") =  VERSION " debug";
#endif
    scope().attr("__author__") = "Gideon May (C) 2016";
    scope().attr("__email__") = "gideon@borges.xyz";
    scope().attr("__credits__") = 
        "Based on the following libraries :\n"
        "    OpenSceneGraph 3.4 (http://www.openscenegraph.org/)\n"
        "    OpenThreads (http://openthreads.sourceforge.net/)\n"
        "    Boost Python Library V2 (1.33.0) (http://www.boost.org/)\n";
    scope().attr("__build__") = buildinfo();
    __init_osg();
}

#include "module_tail.hpp"

