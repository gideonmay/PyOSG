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



