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

#include <osg/Group>

#include <boost/python/return_value_policy.hpp>
#include <boost/python/class.hpp>
#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::Group, osg::ref_ptr<osg::Group>, bases<osg::Node> > class_Group;
extern class_Group * GroupClass;      // Initialized in osg/Group.cpp

template <class F> void register_castGroup(const char * name, F f)
{
    if (GroupClass) {
        GroupClass->def(name, f, return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_GROUP_CAST(NAME)    osg::NAME * as##NAME(osg::Group * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_GROUP_CAST(NAME)  register_castGroup("as" #NAME, &as##NAME);



