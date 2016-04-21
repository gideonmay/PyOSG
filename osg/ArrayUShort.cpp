#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayUShort()
{
    TemplateIndexArray<osg::UShortArray, int>  UShortArray("UShortArray");
}
}
