#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayShort()
{
    TemplateIndexArray<osg::ShortArray, int> ShortArray("ShortArray");
}
}

