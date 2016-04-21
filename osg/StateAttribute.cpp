#include <boost/python.hpp>

#include "StateAttribute.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace PyOSG {

class_StateAttribute * StateAttributeClass = NULL;

typedef enum_<osg::StateAttribute::Values> Values;
typedef enum_<osg::StateAttribute::Type> Type;

void init_StateAttribute()
{

    StateAttributeClass = new class_StateAttribute("StateAttribute", no_init);

    scope stateattribute_class(*StateAttributeClass);

#if 0
        "list values which can be used in to set either GLModeValues"
        "or OverrideValues. When using in conjunction with GLModeValues"
        "all Values have meaning.  When using in conjection with "
        "StateAttribute OverrideValue only OFF,OVERRIDE and INHERIT"
        "are meaningful. However, they are useful when using GLModeValue "
        "and OverrideValue in conjunction with each other as when using"
        "StateSet::setAttributeAndModes(..)."
#endif

    // class_<osg::StateAttribute::ModeUsage> modeUsage("ModeUsage");

    Values values("StateAttribute_Values");
#   define OSG_ENUM_VALUES(VALUE) values.value(#VALUE, osg::StateAttribute::VALUE)
    OSG_ENUM_VALUES(OFF);
    OSG_ENUM_VALUES(ON);
    OSG_ENUM_VALUES(OVERRIDE);
    OSG_ENUM_VALUES(PROTECTED);
    OSG_ENUM_VALUES(INHERIT);
    values.export_values();
#   undef OSG_ENUM_VALUES

        /** Values of StateAttribute::Type used to aid identification
          * of different StateAttribute subclasses. Each subclass defines
          * it own value in the virtual Type getType() method.  When 
          * extending the osg's StateAttribute's simply define your
          * own Type value which is unique, using the StateAttribute::Type
          * enum as a guide of what values to use.  If your new subclass
          * needs to override a standard StateAttriubte then simple use 
          * that types value. */

    Type type("StateAttribute_Type");
#   define OSG_ENUM_TYPE(VALUE) type.value(#VALUE, osg::StateAttribute::VALUE)
    OSG_ENUM_TYPE(TEXTURE);
    OSG_ENUM_TYPE(POLYGONMODE);
    OSG_ENUM_TYPE(POLYGONOFFSET);
    OSG_ENUM_TYPE(MATERIAL);
    OSG_ENUM_TYPE(ALPHAFUNC);
    OSG_ENUM_TYPE(ANTIALIAS);
    OSG_ENUM_TYPE(COLORTABLE);
    OSG_ENUM_TYPE(CULLFACE);
    OSG_ENUM_TYPE(FOG);
    OSG_ENUM_TYPE(FRONTFACE);
    OSG_ENUM_TYPE(LIGHT);
    OSG_ENUM_TYPE(POINT);
    OSG_ENUM_TYPE(LINEWIDTH);
    OSG_ENUM_TYPE(LINESTIPPLE);
    OSG_ENUM_TYPE(POLYGONSTIPPLE);
    OSG_ENUM_TYPE(SHADEMODEL);
    OSG_ENUM_TYPE(TEXENV);
    OSG_ENUM_TYPE(TEXGEN);
    OSG_ENUM_TYPE(TEXMAT);
    OSG_ENUM_TYPE(LIGHTMODEL);
    OSG_ENUM_TYPE(BLENDFUNC);
    OSG_ENUM_TYPE(STENCIL);
    OSG_ENUM_TYPE(COLORMASK);
    OSG_ENUM_TYPE(DEPTH);
    OSG_ENUM_TYPE(VIEWPORT);
    OSG_ENUM_TYPE(CLIPPLANE);
    OSG_ENUM_TYPE(COLORMATRIX);

    OSG_ENUM_TYPE(VERTEXPROGRAM);
    OSG_ENUM_TYPE(FRAGMENTPROGRAM);

    OSG_ENUM_TYPE(POINTSPRITE);

    // cor GLSL support
    OSG_ENUM_TYPE(PROGRAM);

    // ogFX namespace
    OSG_ENUM_TYPE(VALIDATOR);
    OSG_ENUM_TYPE(VIEWMATRIXEXTRACTOR);

    // osNV namespace
    OSG_ENUM_TYPE(OSGNV_PARAMETER_BLOCK);

    // osNVExt namespace
    OSG_ENUM_TYPE(OSGNVEXT_TEXTURE_SHADER);
    OSG_ENUM_TYPE(OSGNVEXT_VERTEX_PROGRAM);
    OSG_ENUM_TYPE(OSGNVEXT_REGISTER_COMBINERS);

    // osgNVCg namespace
    OSG_ENUM_TYPE(OSGNVCG_PROGRAM);

    // osgNVSlang namespace
    OSG_ENUM_TYPE(OSGNVSLANG_PROGRAM);

    // osNVParse
    OSG_ENUM_TYPE(OSGNVPARSE_PROGRAM_PARSER);
    type.export_values();
#undef OSG_ENUM_TYPE
}
}
