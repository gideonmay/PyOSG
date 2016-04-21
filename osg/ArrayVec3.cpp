#include "TemplateCompArray.hpp"

namespace PyOSG {
void init_ArrayVec3()
{
    TemplateCompArray<osg::Vec3Array, osg::Vec3> Vec3Array("Vec3Array");
}
}
