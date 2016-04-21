#include <boost/python/return_value_policy.hpp>
#include <boost/python/class.hpp>

#include <osg/Geode>

#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::Geode, osg::ref_ptr<osg::Geode>, bases<osg::Node> > class_Geode;
extern class_Geode * GeodeClass;      // Initialized in osg/Geode.cpp

template <class F> void register_castGeode(const char * name, F f)
{
    if (GeodeClass) {
        GeodeClass->def(name, f, return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_GEODE_CAST(NAME)    osg::NAME * as##NAME(osg::Geode * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_GEODE_CAST(NAME)  register_castGeode("as" #NAME, &as##NAME);


