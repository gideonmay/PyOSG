#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayUInt()
{
    TemplateIndexArray<osg::UIntArray, int> UIntArray("UIntArray");
}
}
