#include "TemplateIndexArray.hpp"

namespace PyOSG {
void init_ArrayInt()
{
    TemplateIndexArray<osg::IntArray, int> IntArray("IntArray");
}
}

