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

#include <osg/CopyOp>

using namespace boost::python;

namespace PyOSG {
void init_CopyOp()
{
    class_<osg::CopyOp> copy_op("CopyOp");

    copy_op
        .def(init<osg::CopyOp::CopyFlags>())
        ;

    scope copy_op_scope(copy_op);

#   define OSG_ENUM_OPTIONS(VALUE) options.value(#VALUE, osg::CopyOp::VALUE)
    enum_<osg::CopyOp::Options> options("Options");
    OSG_ENUM_OPTIONS(SHALLOW_COPY);
    OSG_ENUM_OPTIONS(DEEP_COPY_OBJECTS);
    OSG_ENUM_OPTIONS(DEEP_COPY_NODES);
    OSG_ENUM_OPTIONS(DEEP_COPY_DRAWABLES);
    OSG_ENUM_OPTIONS(DEEP_COPY_STATESETS);
    OSG_ENUM_OPTIONS(DEEP_COPY_STATEATTRIBUTES);
    OSG_ENUM_OPTIONS(DEEP_COPY_TEXTURES);
    OSG_ENUM_OPTIONS(DEEP_COPY_IMAGES);
    OSG_ENUM_OPTIONS(DEEP_COPY_ARRAYS);
    OSG_ENUM_OPTIONS(DEEP_COPY_PRIMITIVES);
    OSG_ENUM_OPTIONS(DEEP_COPY_SHAPES);
    OSG_ENUM_OPTIONS(DEEP_COPY_ALL);
    options.export_values();
}
}

