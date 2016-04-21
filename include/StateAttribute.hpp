#ifndef  PYOSG_STATE_ATTRIBUTE
#define  PYOSG_STATE_ATTRIBUTE 1

#include <osg/ref_ptr>
#include <osg/StateAttribute>

#include <boost/python/class.hpp>
#include <boost/python/return_value_policy.hpp>
#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::StateAttribute, osg::ref_ptr<osg::StateAttribute>, bases<osg::Object>, boost::noncopyable > class_StateAttribute;
extern class_StateAttribute * StateAttributeClass;

template <class F> void register_castStateAttribute(const char * name, F f)
{
    if (StateAttributeClass) {
        StateAttributeClass->def(name, f, boost::python::return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_STATEATTRIBUTE_CAST(NAME)    osg::NAME * as##NAME(osg::StateAttribute * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_STATEATTRIBUTE_CAST(NAME)  register_castStateAttribute("as" #NAME, &as##NAME);

#endif

