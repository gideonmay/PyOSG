// Copyright (C) 2002-2003 Gideon May (gideon@computer.org)
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
#include <boost/python/operators.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/detail/api_placeholder.hpp>

#include <osg/Vec2>

#include <string>
#include <iostream>
#include <sstream>

using namespace boost::python;

namespace {

osg::Vec2* vec2tuple(tuple data)
{
    float x = 0, y = 0;

    // Fall through intentionally!
    switch (len(data)) {
        case 2: y = extract<float>(data[1]);
        case 1: x = extract<float>(data[0]);
    }
    return new osg::Vec2(x, y);
}

std::string osgVec2_repr(osg::Vec2 * self)
{
    std::ostringstream ost;
    ost << "Vec2(" << self->_v[0] << "," << self->_v[1] << ")";
    return ost.str();
}

std::string osgVec2_str(osg::Vec2 * self)
{
    std::ostringstream ost;
    ost << "(" << self->_v[0] << " " << self->_v[1] << ")";
    return ost.str();
}

inline void set(osg::Vec2 * self, osg::Vec2& from) { * self = from; }

void __setitem__(osg::Vec2 * self, int idx, float val) { (*self)[idx] = val; }
float __getitem__(osg::Vec2 * self, int idx) { return (*self)[idx]; }

inline float get_x(osg::Vec2 * self) { return self->_v[0]; }
inline void  set_x(osg::Vec2 * self, float x) { self->_v[0] = x; }

inline float get_y(osg::Vec2 * self) { return self->_v[1]; }
inline void  set_y(osg::Vec2 * self, float y) { self->_v[1] = y; }

} // namespace

namespace PyOSG {
void init_Vec2()
{
    // Complete
    class_<osg::Vec2>("Vec2")
        .def(init<float, float>())
        .def(init<osg::Vec2&>())
        .def("__init__", make_constructor(vec2tuple))

        .def(self == self)
        .def(self != self)
        .def(self < self)

//        .def("set", &osg::Vec2::set)
        .def("set", &set)
        .def("__setitem__", &__setitem__)
#ifdef WIN32
        .def("__getitem__", &__getitem__)
        .def("x", get_x)
        .def("y", get_y)
#else
        .def("__getitem__",
            (float &(osg::Vec2::*)(int)) &osg::Vec2::operator[],
            return_value_policy<copy_non_const_reference>())
        .def("x", (float (osg::Vec2::*)() const) &osg::Vec2::x)
        .def("y", (float (osg::Vec2::*)() const) &osg::Vec2::y)
#endif
        .add_property("_x", get_x, set_x)
        .add_property("_y", get_y, set_y)
        .def("valid", &osg::Vec2::valid)
        .def("isNaN", &osg::Vec2::isNaN)
        .def(self * self)
        .def(self * float())
        .def(self *= float())
        .def(self / float())
        .def(self /= float())
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(-self)
        .def("length", &osg::Vec2::length)
        .def("length2", &osg::Vec2::length2)
        .def("normalize", &osg::Vec2::normalize)
        .def("__str__", &osgVec2_str)
        .def("__repr__", &osgVec2_repr)
        ;
}
}
