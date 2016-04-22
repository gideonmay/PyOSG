// Copyright (C) 2016 Gideon May (gideon@borges.xyz)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

#include <boost/python/class.hpp>

#include <osg/BoundingSphere>
#include <iostream>

#include "held_ptr.hpp"

using namespace boost::python;
namespace {
void osgBoundingSphere_radius(osg::BoundingSphere * self, float radius)
{
    self->radius() = radius;
}

std::string osgBoundingSphere_str(osg::BoundingSphere * self)
{
    std::ostringstream ost;
    ost << "(" << self->_center[0] << "," << self->_center[1] << "," << self->_center[2] << ")," << self->_radius << "";
    return ost.str();
}

std::string osgBoundingSphere_repr(osg::BoundingSphere * self)
{
    std::ostringstream ost;
    ost << "BoundingSphere((" << self->_center[0] << "," << self->_center[1] << "," << self->_center[2] << ")," << self->_radius << ")";
    return ost.str();
}

}

namespace PyOSG {
void init_BoundingSphere()
{
    class_<osg::BoundingSphere>("BoundingSphere",
            "General purpose bounding sphere class for enclosing nodes/objects/vertices.\n"
            "Used to bound internal osg::Node's in the scene,\n"
            "to assist in view frustum culling etc.  Similar in function to BoundingBox\n"
            "but is quicker for evaluating culling, but generally encloses a greater volume\n"
            "than a BoundingBox so will not cull so aggressively.\n")
        .def_readwrite("_center", &osg::BoundingSphere::_center)
        .def_readwrite("_radius", &osg::BoundingSphere::_radius)
        .def(init<osg::Vec3, float>())
        .def("init", &osg::BoundingSphere::init,
            "initialize to invalid values to represent an unset bounding sphere.")
        .def("valid", &osg::BoundingSphere::valid,
            "return true if the bounding sphere contains valid values,\n"
            "false if the bounding sphere is effectively unset.")
        .def("set", 
            &osg::BoundingSphere::set,
            "set bounding sphere.")
        .def("center", 
            (osg::Vec3&(osg::BoundingSphere::*)()) &osg::BoundingSphere::center,
            return_internal_reference<>())
        .def("radius", 
            (float(osg::BoundingSphere::*)()const)&osg::BoundingSphere::radius)
        .def("radius",
            &osgBoundingSphere_radius)
        .def("contains", &osg::BoundingSphere::contains,
            "return true is vertex v is within the sphere.")
        .def("intersects", &osg::BoundingSphere::intersects,
            "return true if bounding sphere's intersect each other.")
        .def("__str__", &osgBoundingSphere_str)
        .def("__repr__", &osgBoundingSphere_repr)
        ;
}
} // namespace PyOSG
