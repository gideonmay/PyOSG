#include <osg/Transform>

#include <boost/python/return_value_policy.hpp>
#include <boost/python/class.hpp>
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
