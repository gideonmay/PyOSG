#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayUByte()
{
    TemplateIndexArray<osg::UByteArray, int> UByteArray("UByteArray");
}
}
