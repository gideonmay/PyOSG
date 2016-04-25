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
#include <boost/ref.hpp>

#include <osg/ClearNode>

#include <string>
#include <iostream>

#include "Group.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
DEFINE_GROUP_CAST(ClearNode)
}


namespace PyOSG {
void init_ClearNode()
{
    REGISTER_GROUP_CAST(ClearNode)

    class_<osg::ClearNode, osg::ref_ptr<osg::ClearNode>, bases<osg::Group> >("ClearNode",
        "ClearNode is a Group node which controls the clearing of the color and depth\n"
        "buffers at the start of each frame.\n"
        "The earth sky by default is empty and simply holds the clear color of\n"
        "the background. However, if the uses wants to add their own clearing of\n"
        "the color and depth buffers then the children can be added, and the\n"
        "background clear turned off. The ClearNode by default has StateSet attached\n"
        "to it which sets the default ClearNode bin number to -1, so that all drawables\n"
        "below it are placed in a separate bin from the rest of the scene graph, and\n"
        "are rendered prior to standard opaque and transparent drawables.",
        no_init)
     .def(init<>())

     .def("setRequiresClear",
        &osg::ClearNode::setRequiresClear,
        "Sets the flag which control whether a glClear is required at the beginning of each frame.")

     .def("getRequiresClear",
        &osg::ClearNode::getRequiresClear,
        "Gets the flag which control whether a glClear is required at the beginning of each frame.")
     .def("setClearColor",
        &osg::ClearNode::setClearColor,
        "Sets the clear color.")
     .def("getClearColor",
        &osg::ClearNode::getClearColor,
        return_value_policy<copy_const_reference>(),
        "Returns the clear color.")

     .def("setClearMask",
        &osg::ClearNode::setClearMask)
     .def("getClearMask",
        &osg::ClearNode::getClearMask)
     ;
}
}
