#include "TemplateCompArray.hpp"

namespace PyOSG {
void init_ArrayVec4()
{
    TemplateCompArray<osg::Vec4Array, osg::Vec4> Vec4Array("Vec4Array");
}
}
