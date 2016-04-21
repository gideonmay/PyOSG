#include "TemplateArray.hpp"

namespace PyOSG {
void init_ArrayFloat()
{
    TemplateArray<osg::FloatArray, float> FloatArray("FloatArray");
}
}
