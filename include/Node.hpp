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

#include <osg/Node>

#include <boost/python.hpp>
#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::Node, osg::ref_ptr<osg::Node>, bases<osg::Object> > class_Node;
extern class_Node * NodeClass;      // Initialized in osg/Node.cpp

template <class F> void register_castNode(const char * name, F f)
{
    if (NodeClass) {
        NodeClass->def(name, f, return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_NODE_CAST(NAME)    osg::NAME * as##NAME(osg::Node * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_NODE_CAST(NAME)  register_castNode("as" #NAME, &as##NAME);

