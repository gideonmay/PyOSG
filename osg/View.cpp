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

#include <osg/View>

using namespace boost::python;

namespace {

}

namespace PyOSG {
    void init_View() {
        class_<osg::View, osg::ref_ptr<osg::View>, bases<osg::Object> > view("View", no_init);

        view
            .def(init<>())
            .def("setStats", &osg::View::setStats)
//            .def("getStats", &osg::View::getStats)

            .def("setLightingMode", &osg::View::setLightingMode)
            .def("getLightingMode", &osg::View::getLightingMode)

            .def("setLight", &osg::View::setLight)
//            .def("getLight", (osg::Light * (osg::View::*)(void)) &osg::View::getLight)

            .def("setCamera", &osg::View::setCamera)
//            .def("getCamera", &osg::View::getCamera)

            .def("setFrameStamp", &osg::View::setFrameStamp)
//            .def("getFrameStamp", &osg::View::getFrameStamp)
        ;

        scope view_scope(view);

        enum_<osg::View::LightingMode> lighting_mode("View_LightingMode");
#       define OSG_ENUM_TYPE(VALUE) lighting_mode.value(#VALUE, osg::View::VALUE)
        OSG_ENUM_TYPE(NO_LIGHT);
        OSG_ENUM_TYPE(HEADLIGHT);
        OSG_ENUM_TYPE(SKY_LIGHT);
        lighting_mode.export_values();
    }
}
