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

#include <osg/StateAttribute>
#include <osg/Light>

#include "StateAttribute.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
osg::Light * asLight(osg::StateAttribute * self) { return dynamic_cast<osg::Light*>(self); }
}

namespace PyOSG {
void init_Light()
{

    register_castStateAttribute("asLight", &asLight);

    class_<osg::Light, osg::ref_ptr<osg::Light>, bases<osg::StateAttribute> , boost::noncopyable >("Light", no_init)
        .def(init<>())
        .def("setLightNum", &osg::Light::setLightNum)
        .def("getLightNum", (int (osg::Light::*)()const)&osg::Light::getLightNum)
        .def("setAmbient", &osg::Light::setAmbient)
        .def("getAmbient", &osg::Light::getAmbient, return_value_policy<copy_const_reference>())
        .def("setDiffuse", &osg::Light::setDiffuse)
        .def("getDiffuse", &osg::Light::getDiffuse, return_value_policy<copy_const_reference>())
        .def("setSpecular", &osg::Light::setSpecular)
        .def("getSpecular", &osg::Light::getSpecular, return_value_policy<copy_const_reference>())
        .def("setPosition", &osg::Light::setPosition)
        .def("getPosition", &osg::Light::getPosition, return_value_policy<copy_const_reference>())
        .def("setDirection", &osg::Light::setDirection)
        .def("getDirection", &osg::Light::getDirection, return_value_policy<copy_const_reference>())
        .def("setConstantAttenuation", &osg::Light::setConstantAttenuation)
        .def("getConstantAttenuation", &osg::Light::getConstantAttenuation)
        .def("setLinearAttenuation", &osg::Light::setLinearAttenuation)
        .def("getLinearAttenuation", &osg::Light::getLinearAttenuation)
        .def("setQuadraticAttenuation", &osg::Light::setQuadraticAttenuation)
        .def("getQuadraticAttenuation", &osg::Light::getQuadraticAttenuation)
        .def("setSpotExponent", &osg::Light::setSpotExponent)
        .def("getSpotExponent", &osg::Light::getSpotExponent)
        .def("setSpotCutoff", &osg::Light::setSpotCutoff)
        .def("getSpotCutoff", &osg::Light::getSpotCutoff)
        .def("captureLightState", &osg::Light::captureLightState)
         ;

}

} // namespace PyOSG
