#include <boost/python.hpp>

#include <osg/LightModel>

#include "StateAttribute.hpp"
#include "held_ptr.hpp"

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
