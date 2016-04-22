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

#include <osg/Transform>

#include <boost/python.hpp>
#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::Transform, osg::ref_ptr<osg::Transform>, bases<osg::Group> > class_Transform;
extern class_Transform * TransformClass; // Initialized in osg/Transform.cpp

template <class F> void register_castTransform(const char * name, F f)
{
    if (TransformClass) {
        TransformClass->def(name, f, return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_TRANSFORM_CAST(NAME)    osg::NAME * as##NAME(osg::Transform * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_TRANSFORM_CAST(NAME)  register_castTransform("as" #NAME, &as##NAME);
