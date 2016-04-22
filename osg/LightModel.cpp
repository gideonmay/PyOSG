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

#include <osg/LightModel>

#include "StateAttribute.hpp"

using namespace boost::python;

namespace {
osg::LightModel * asLightModel(osg::StateAttribute * self) { return dynamic_cast<osg::LightModel*>(self); }
}

namespace PyOSG {
void init_LightModel()
{
    register_castStateAttribute("asLightModel", &asLightModel);

    class_<osg::LightModel, osg::ref_ptr<osg::LightModel>, bases<osg::StateAttribute> > lightModel("LightModel", no_init);

    scope osg_lightModel(lightModel);
    lightModel
        .def(init<>())

        .def("setAmbientIntensity", &osg::LightModel::setAmbientIntensity)
        .def("getAmbientIntensity", &osg::LightModel::getAmbientIntensity, return_value_policy<copy_const_reference>())
        .def("setColorControl", &osg::LightModel::setColorControl)
        .def("getColorControl", &osg::LightModel::getColorControl)
        .def("setLocalViewer", &osg::LightModel::setLocalViewer)
        .def("getLocalViewer", &osg::LightModel::getLocalViewer)
        .def("setTwoSided", &osg::LightModel::setTwoSided)
        .def("getTwoSided", &osg::LightModel::getTwoSided)
        ;

#   define OSG_ENUM_CC(VALUE) cc.value(#VALUE, osg::LightModel::VALUE)
    enum_<osg::LightModel::ColorControl> cc("ColorControl");
    OSG_ENUM_CC(SEPARATE_SPECULAR_COLOR);
    OSG_ENUM_CC(SINGLE_COLOR);
    cc.export_values();
}
} // namespace PyOSG
