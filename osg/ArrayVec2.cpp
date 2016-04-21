#include "TemplateCompArray.hpp"

namespace PyOSG {
void init_ArrayVec2()
{
    TemplateCompArray<osg::Vec2Array, osg::Vec2> Vec2Array("Vec2Array");
}
}
