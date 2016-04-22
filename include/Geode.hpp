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


