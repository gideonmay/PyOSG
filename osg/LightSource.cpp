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

#include <osg/LightSource>

#include <string>
#include <iostream>

#include "Node.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
DEFINE_NODE_CAST(LightSource)

void setLocalStateSetModes(osg::LightSource & self)
{
    self.setLocalStateSetModes();
}

}

namespace PyOSG {
void init_LightSource()
{
    REGISTER_NODE_CAST(LightSource)

    class_<osg::LightSource, osg::ref_ptr<osg::LightSource>, bases<osg::Group> > lightsource("LightSource", 
        "Leaf Node for defining a light in the scene.",
         no_init);

    scope lightsource_scope(lightsource);

    lightsource
        .def(init<>())
        .def("setReferenceFrame", &osg::LightSource::setReferenceFrame)
        .def("getReferenceFrame", &osg::LightSource::getReferenceFrame)
        .def("setLight", &osg::LightSource::setLight)
        .def("getLight", 
            (osg::Light* (osg::LightSource::*)())
            &osg::LightSource::getLight, 
            return_value_policy<manage_osg_object>())
        .def("setStateSetModes", &osg::LightSource::setStateSetModes)
        .def("setLocalStateSetModes", &osg::LightSource::setLocalStateSetModes)
        .def("setLocalStateSetModes", &setLocalStateSetModes)
        ;

#   define OSG_ENUM_FRAME(VALUE) frame.value(#VALUE, osg::LightSource::VALUE)
    enum_<osg::LightSource::ReferenceFrame> frame("ReferenceFrame");
    OSG_ENUM_FRAME(RELATIVE_RF);
    OSG_ENUM_FRAME(ABSOLUTE_RF);
    frame.export_values();
}
}
