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

#include <boost/python.hpp>

#include <sstream>
#include <string>
#include <iostream>

#include <osg/Quat>
#include <osg/Matrix>

#include "Math.hpp"

using namespace boost::python;

namespace {
osg::Quat* Quat_tuple(tuple data)
{
    osg::Quat::value_type x = 0, y = 0, z = 0, a = 1;

    // Fall through intentionally!
    switch (len(data)) {
        case 4: a = extract<osg::Quat::value_type>(data[3]);
        case 3: z = extract<osg::Quat::value_type>(data[2]);
        case 2: y = extract<osg::Quat::value_type>(data[1]);
        case 1: x = extract<osg::Quat::value_type>(data[0]);
        default: break;

    }
    return new osg::Quat(x, y, z, a);
}

void set_tuple(osg::Quat& self, tuple data)
{
    osg::Quat::value_type x = 0, y = 0, z = 0, a = 1;

    // Fall through intentionally!
    switch (len(data)) {
        case 4: a = extract<osg::Quat::value_type>(data[3]);
        case 3: z = extract<osg::Quat::value_type>(data[2]);
        case 2: y = extract<osg::Quat::value_type>(data[1]);
        case 1: x = extract<osg::Quat::value_type>(data[0]);
        default: break;
    }
    self.set(x, y, z, a);
}

std::string osgQuat_str(osg::Quat * self)
{
    std::ostringstream ost;
    ost << "(" << self->_v[0] << " " << self->_v[1] << " " << self->_v[2] << " " << self->_v[3] << ")";
    return ost.str();
}

std::string osgQuat_repr(osg::Quat * self)
{
    std::ostringstream ost;
    ost << "Quat(" << self->_v[0] << "," << self->_v[1] << "," << self->_v[2] << "," << self->_v[3] << ")";
    return ost.str();
}

const tuple osgQuat_getRotate(osg::Quat* q)
{
    osg::Quat::value_type angle, x, y, z;
    q->getRotate(angle, x, y, z);
    return boost::python::make_tuple(angle, x, y, z);
}

void set(osg::Quat * self, osg::Quat& from) { * self = from; }

void __setitem__(osg::Quat * self, int idx, osg::Quat::value_type val) { (*self)[idx] = val; }

osg::Quat::value_type get_x(osg::Quat * self) { return self->_v[0]; }
void  set_x(osg::Quat * self, osg::Quat::value_type x) { self->_v[0] = x; }

osg::Quat::value_type get_y(osg::Quat * self) { return self->_v[1]; }
void  set_y(osg::Quat * self, osg::Quat::value_type y) { self->_v[1] = y; }

osg::Quat::value_type get_z(osg::Quat * self) { return self->_v[2]; }
void  set_z(osg::Quat * self, osg::Quat::value_type z) { self->_v[2] = z; }

osg::Quat::value_type get_w(osg::Quat * self) { return self->_v[3]; }
void  set_w(osg::Quat * self, osg::Quat::value_type a) { self->_v[3] = a; }
}


namespace PyOSG {
void init_Quat()
{
    class_<osg::Quat> quat("Quat");
    quat
        .def(init<osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type>())
        .def(init<const osg::Vec4&>())
        .def(init<osg::Quat::value_type, const osg::Vec3&>())
        .def(init<osg::Quat::value_type, const osg::Vec3&, osg::Quat::value_type, const osg::Vec3&, osg::Quat::value_type, const osg::Vec3&>())
        .def("__init__", make_constructor(Quat_tuple))
    ;quat
        .def("asVec4", (osg::Vec4&(osg::Quat::*)()) &osg::Quat::asVec4, return_internal_reference<>())
        .def("asVec3", (osg::Vec3&(osg::Quat::*)()) &osg::Quat::asVec3, return_value_policy<return_by_value>())
        .def("set", (void (osg::Quat::*)(osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type))&osg::Quat::set)
        .def("set", (void (osg::Quat::*)(const osg::Vec4&))&osg::Quat::set)
        .def("set", &set_tuple)
#ifdef OSG_USE_DOUBLE_MATRICES
        .def("set", (void (osg::Quat::*)(const osg::Matrixd&))&osg::Quat::set)
#else
        .def("set", (void (osg::Quat::*)(const osg::Matrixf&))&osg::Quat::set)
#endif
    ;quat
        .def("__getitem__", (osg::Quat::value_type &(osg::Quat::*)(int)) &osg::Quat::operator[], return_value_policy<copy_non_const_reference>())
    ;quat
        .def("__setitem__", &__setitem__)
    ;quat

        .def("x", (osg::Quat::value_type (osg::Quat::*)() const)&osg::Quat::x)
        .def("y", (osg::Quat::value_type (osg::Quat::*)() const)&osg::Quat::y)
        .def("z", (osg::Quat::value_type (osg::Quat::*)() const)&osg::Quat::z)
        .def("w", (osg::Quat::value_type (osg::Quat::*)() const)&osg::Quat::w)

        .add_property("_x", &get_x, &set_x)
        .add_property("_y", &get_y, &set_y)
        .add_property("_z", &get_z, &set_z)
        .add_property("_w", &get_w, &set_w)

        .def("zeroRotation", &osg::Quat::zeroRotation,
            "return true if the Quat represents a zero rotation, and therefore can be ignored in computations.")

        .def(self * osg::Quat::value_type())
        .def(self *= osg::Quat::value_type())
        .def(self * self)
        .def(self *= self)

        .def(self / osg::Quat::value_type())
        .def(self /= osg::Quat::value_type())
        .def(self / self)
        .def(self /= self)

        .def(self + self)
        .def(self += self)

        .def(self - self)
        .def(self -= self)
        .def(-self)

        .def("length", &osg::Quat::length,
            "Length of the quaternion = sqrt( vec . vec )")

        .def("length2", &osg::Quat::length2,
            "Length of the quaternion =  vec . vec ")

        .def("conj", &osg::Quat::conj, "Conjugate")

        .def("inverse", &osg::Quat::inverse,
            "Multiplicative inverse method: q^(-1) = q^*/(q.q^*)")

        .def("makeRotate", (void (osg::Quat::*)(osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type, osg::Quat::value_type))&osg::Quat::makeRotate)
        .def("makeRotate", (void (osg::Quat::*)(osg::Quat::value_type, const osg::Vec3&))&osg::Quat::makeRotate)
        .def("makeRotate", (void (osg::Quat::*)(const osg::Vec3&, const osg::Vec3&))&osg::Quat::makeRotate,
            "Make a rotation Quat which will rotate vec1 to vec2.\n"
            "Generally take adot product to get the angle between these\n"
            "and then use a cross product to get the rotation axis\n"
            "Watch out for the two special cases of when the vectors\n"
            "are co-incident or opposite in direction.\n")

        .def("getRotate", &osgQuat_getRotate)

        .def("slerp", &osg::Quat::slerp,
            "Spherical Linear Interpolation.\n"
            "As t goes from 0 to 1, the Quat object goes from 'from' to 'to'. \n")
#ifdef OSG_USE_DOUBLE_MATRICES
        .def("set", (void(osg::Quat::*)(const osg::Matrixd&)) &osg::Quat::set,
#else
        .def("set", (void(osg::Quat::*)(const osg::Matrixf&)) &osg::Quat::set,
#endif
            "Set quaternion to be equivalent to specified matrix.")
#ifdef OSG_USE_DOUBLE_MATRICES
        .def("get", (void (osg::Quat::*)(osg::Matrixd&) const) &osg::Quat::get,
#else
        .def("get", (void (osg::Quat::*)(osg::Matrixf&) const) &osg::Quat::get,
#endif
            "Get the equivalent matrix for this quaternion.")

        .def("__str__", &osgQuat_str)
        .def("__repr__", &osgQuat_repr)
        ;
}
} // namespace
