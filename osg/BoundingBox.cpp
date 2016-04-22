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

#include <osg/BoundingBox>
#include <osg/BoundingSphere>

#include <string>
#include <iostream>

using namespace boost::python;

namespace {
std::string BoundingBox_str(osg::BoundingBox * self)
{
    std::ostringstream ost;
    ost << "(" << self->_min[0] << "," << self->_min[1] << "," << self->_min[2] << ") (" << self->_max[0] << "," << self->_max[1] << "," << self->_max[2] << ")";
    return ost.str();
}

std::string BoundingBox_repr(osg::BoundingBox * self)
{
    std::ostringstream ost;
    ost << "BoundingBox((" << self->_min[0] << "," << self->_min[1] << "," << self->_min[2] << "),(" << self->_max[0] << "," << self->_max[1] << "," << self->_max[2] << "))";
    return ost.str();
}

} // namespace
namespace PyOSG {
void init_BoundingBox()
{
    class_<osg::BoundingBox> bounding_box("BoundingBox",
            "General purpose axis-aligned bounding box class for enclosing objects/vertices.\n"
            "Used to bounding the leaf objects in the scene,\n"
            "i.e. osg::Drawable's to assist in view frustum culling etc.\n");

    bounding_box
        .def_readwrite("_min", &osg::BoundingBox::_min)
        .def_readwrite("_max", &osg::BoundingBox::_max)
        .def(init<>())
        .def(init<float, float, float, float, float, float>())
            // "construct to with specified min and max values.\n")

        .def(init<osg::Vec3, osg::Vec3>())
            // "construct to with specified min and max values.\n")

        .def("init", &osg::BoundingBox::init,
            "initialize to invalid values to represent an unset bounding box.")

        .def("valid", &osg::BoundingBox::valid)

        .def("set",
            (void (osg::BoundingBox::*)(float, float, float, float, float, float))
            &osg::BoundingBox::set)
        .def("set",
            (void (osg::BoundingBox::*)(const osg::Vec3&, const osg::Vec3 &))
            &osg::BoundingBox::set)

        .def("xMin", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::xMin)
        .def("yMin", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::yMin)
        .def("zMin", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::zMin)
        .def("xMax", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::xMax)
        .def("yMax", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::yMax)
        .def("zMax", (float (osg::BoundingBox::*)() const)&osg::BoundingBox::zMax)

        .def("center",
            &osg::BoundingBox::center,
            "Calculate and return the center of the bounding box.\n")

        .def("radius",
            &osg::BoundingBox::radius,
            "Calculate and return the radius of the bounding box.\n")

        .def("radius2",
            &osg::BoundingBox::radius2,
            "Calculate and return the radius squared of the bounding box.\n"
            "Note, radius2() is faster to calculate than radius().\n")

        .def("corner",
            &osg::BoundingBox::corner,
            "corner(pos) -> Vec3\n\n"
            "return the corner of the bounding box.\n"
            "Position (pos) is specified by a number between 0 and 7,\n"
            "the first bit toggles between x min and x max, second\n"
            "bit toggles between y min and y max, third bit toggles\n"
            "between z min and z max.\n")

        .def("expandBy", 
            (void(osg::BoundingBox::*)(const osg::Vec3&)) &osg::BoundingBox::expandBy)
        .def("expandBy", 
            (void(osg::BoundingBox::*)(float, float, float)) &osg::BoundingBox::expandBy)
        .def("expandBy",
            (void(osg::BoundingBox::*)(const osg::BoundingBox&)) &osg::BoundingBox::expandBy)
        .def("expandBy",
            (void(osg::BoundingBox::*)(const osg::BoundingSphere&)) &osg::BoundingBox::expandBy)
        .def("intersect",
            &osg::BoundingBox::intersect)
        .def("intersects",
            &osg::BoundingBox::intersects)
//        .def("contains",
//            &osg::BoundingBox::contains)
        .def("__str__",
            &BoundingBox_str)
        .def("__repr__",
            &BoundingBox_repr)
        ;
}
} // namespace PyOSG
