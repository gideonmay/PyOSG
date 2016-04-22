#include <boost/python.hpp>

#include <osg/Material>

#include "StateAttribute.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
osg::Material * asMaterial(osg::StateAttribute * self) { return dynamic_cast<osg::Material*>(self); }
}


namespace PyOSG {
void init_Material()
{
    register_castStateAttribute("asMaterial", &asMaterial);

    class_<osg::Material, osg::ref_ptr<osg::Material>, bases<osg::StateAttribute>, boost::noncopyable > material("Material",
        "Material - encapsulates OpenGL glMaterial state.",
        no_init);
    scope material_scope(material);

    material
         .def(init<>())
         .def("setColorMode", &osg::Material::setColorMode,
                 "setColorMode(mode) -> None\n"
                 "\n"
                 "mode is of type osg.Material.ColorMode")
         .def("getColorMode", &osg::Material::getColorMode,
                 "getColorMode() -> mode\n")
         .def("setAmbient",   &osg::Material::setAmbient,
                 "setAmbient(face, ambient) -> None\n")
         .def("getAmbient",
            &osg::Material::getAmbient,
            return_value_policy<copy_const_reference>(),
            "getAmbient(face) -> ambient\n")
         .def("getAmbientFrontAndBack",   &osg::Material::getAmbientFrontAndBack,
                 "getAmbientFrontAndBack() -> boolean\n")
         .def("setDiffuse",   &osg::Material::setDiffuse)
         .def("getDiffuse",   &osg::Material::getDiffuse, return_value_policy<copy_const_reference>())
         .def("getDiffuseFrontAndBack",   &osg::Material::getDiffuseFrontAndBack)
         .def("setSpecular",   &osg::Material::setSpecular,
            "Set specular value of specified face(s) of the material, \n"
            "valid specular[0..3] range is 0.0 to 1.0.\n")
         .def("getSpecular",   &osg::Material::getSpecular, return_value_policy<copy_const_reference>(),
            "Get the specular value for specified face.\n")
         .def("getSpecularFrontAndBack",   &osg::Material::getSpecularFrontAndBack,
            "Get the whether specular values are equal for front and back faces.\n")
         .def("setEmission",   &osg::Material::setEmission,
            "Set emission value of specified face(s) of the material, \n"
            "valid emmison[0..3] range is 0.0 to 1.0.\n")
         .def("getEmission",   &osg::Material::getEmission, return_value_policy<copy_const_reference>(),
            "Get the emmsion value for specified face.\n")
         .def("getEmissionFrontAndBack",   &osg::Material::getEmissionFrontAndBack,
            "Get the whether emission values are equal for front and back faces.\n")
         .def("setShininess",   &osg::Material::setShininess,
            "Set shininess of specified face(s) of the material, valid shininess range is 0.0 to 128.0.\n")
         .def("getShininess",   &osg::Material::getShininess,
            "Get the shininess value for specified face.\n")
         .def("getShininessFrontAndBack",   &osg::Material::getShininessFrontAndBack,
            "Get the whether shininess values are equal for front and back faces.\n")
         .def("setTransparency",&osg::Material::setTransparency,
            "Set the alpha value of ambient,diffuse,specular and emission colors, \n"
            "of specified face, to 1-transparency. Valid transparency range is 0.0 to 1.0.\n")
         .def("setAlpha",       &osg::Material::setAlpha,
            "Set the alpha value of ambient,diffuse,specular and emission colors.\n"
            "Valid transparency range is 0.0 to 1.0.\n")
         ;

#   define OSG_ENUM_MODE(VALUE) mode.value(#VALUE, osg::Material::VALUE)
    enum_<osg::Material::ColorMode> mode("ColorMode");
    OSG_ENUM_MODE(AMBIENT);
    OSG_ENUM_MODE(DIFFUSE);
    OSG_ENUM_MODE(SPECULAR);
    OSG_ENUM_MODE(EMISSION);
    OSG_ENUM_MODE(AMBIENT_AND_DIFFUSE);
    OSG_ENUM_MODE(OFF);
    mode.export_values();

#   define OSG_ENUM_FACE(VALUE) face.value(#VALUE, osg::Material::VALUE)
    enum_<osg::Material::Face> face("Face");
    OSG_ENUM_FACE(FRONT);
    OSG_ENUM_FACE(BACK);
    OSG_ENUM_FACE(FRONT_AND_BACK);
    face.export_values();
}
}

