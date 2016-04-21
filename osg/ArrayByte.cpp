#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayByte()
{
    TemplateIndexArray<osg::ByteArray, int> ByteArray("ByteArray");
}
}
