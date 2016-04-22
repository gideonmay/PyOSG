// Copyright (C) 2016 Gideon May (gideon@borges.xyz)
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

#include <osgUtil/Version>

using namespace boost::python;

namespace PyOSGUtil {
void init_CubeMapGenerator();
void init_CullVisitor();
void init_DisplayListVisitor();
void init_DisplayRequirementsVisitor();
void init_HalfWayMapGenerator();
void init_HighlightMapGenerator();
void init_IntersectVisitor();
void init_Optimizer();
void init_RenderBin();
void init_RenderStage();
void init_ReflectionMapGenerator();
void init_SceneView();
void init_SmoothingVisitor();
void init_Tessellator();
void init_TransformCallback();
void init_UpdateVisitor();
void init_TriStripVisitor();
void init_DelaunayTriangulator();
void init_TangentSpaceGenerator();
void init_StateGraph();
void init_RenderLeaf();
void init_Simplifier();
}

using namespace PyOSGUtil;

BOOST_PYTHON_MODULE(_osgUtil)
{
    /*
    init_CubeMapGenerator();
    init_CullVisitor();
    init_DisplayRequirementsVisitor();
    init_HalfWayMapGenerator();
    init_HighlightMapGenerator();
    init_IntersectVisitor();
    init_Optimizer();
    init_RenderBin();
    init_RenderStage();
    init_ReflectionMapGenerator();
    init_SceneView();
    init_SmoothingVisitor();
    init_Tessellator();
    init_TransformCallback();
    init_UpdateVisitor();
    init_TriStripVisitor();
    init_DelaunayTriangulator();
    init_TangentSpaceGenerator();
    init_RenderLeaf();
    init_Simplifier();
    init_StateGraph();
    */

    def("GetVersion", (const char *(*)()) &osgUtilGetVersion);
    def("GetLibraryName", (const char *(*)()) &osgUtilGetLibraryName);
}

#include "module_tail.hpp"

