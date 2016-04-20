#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/detail/api_placeholder.hpp>

#include <osg/Vec3>
#include <osg/Vec4>

#include <string>
#include <iostream>
#include <sstream>

using namespace boost::python;

namespace {

osg::Vec4* vec4tuple(tuple data)
{
    float x = 0, y = 0, z = 0, w = 1;

    // Fall through intentionally!
    switch (len(data)) {
        case 4: w = extract<float>(data[3]);
        case 3: z = extract<float>(data[2]);
        case 2: y = extract<float>(data[1]);
        case 1: x = extract<float>(data[0]);
    }
    return new osg::Vec4(x, y, z, w);
}

std::string osgVec4_repr(osg::Vec4 * self)
{
    std::ostringstream ost;
    ost << "Vec4(" << self->_v[0] << "," << self->_v[1] << "," << self->_v[2] << "," << self->_v[3] << ")";
    return ost.str();
}

std::string osgVec4_str(osg::Vec4 * self)
{
    std::ostringstream ost;
    ost << "(" << self->_v[0] << " " << self->_v[1] << " " << self->_v[2] << " " << self->_v[3] << ")";
    return ost.str();
}

#ifdef WIN32
inline void set_floats(osg::Vec4 * self, float x, float y, float z, float w) { self->set(x, y, z, w); }
#endif
inline void set(osg::Vec4 * self, osg::Vec4& from) { * self = from; }

inline void __setitem__(osg::Vec4 * self, int idx, float val) { (*self)[idx] = val; }
inline float __getitem__(osg::Vec3 * self, int idx) { return (*self)[idx]; }

inline float get_x(osg::Vec4 * self) { return self->_v[0]; }
inline void  set_x(osg::Vec4 * self, float x) { self->_v[0] = x; }

inline float get_y(osg::Vec4 * self) { return self->_v[1]; }
inline void  set_y(osg::Vec4 * self, float y) { self->_v[1] = y; }

inline float get_z(osg::Vec4 * self) { return self->_v[2]; }
inline void  set_z(osg::Vec4 * self, float z) { self->_v[2] = z; }

inline float get_w(osg::Vec4 * self) { return self->_v[3]; }
inline void  set_w(osg::Vec4 * self, float z) { self->_v[3] = z; }

} // namespace

namespace PyOSG {
void init_Vec4()
{
    // Complete
    class_<osg::Vec4>("Vec4")
         .def(init<float, float, float, float>())
         .def(init<osg::Vec4&>())
         .def(init<osg::Vec3&, float>())
         .def("__init__", make_constructor(vec4tuple))
         .def(self == self)
         .def(self != self)
         .def(self < self)
#ifdef WIN32
         .def("set", set_floats)
         .def("__getitem__", &__getitem__)
         .def("x", &get_x)
         .def("y", &get_y)
         .def("z", &get_z)
         .def("w", &get_w)
#else
         .def("set", &osg::Vec4::set)
         .def("__getitem__",
            (float &(osg::Vec4::*)(unsigned int)) &osg::Vec4::operator[],
            return_value_policy<copy_non_const_reference>())
         .def("x", (float (osg::Vec4::*)() const) &osg::Vec4::x)
         .def("y", (float (osg::Vec4::*)() const) &osg::Vec4::y)
         .def("z", (float (osg::Vec4::*)() const) &osg::Vec4::z)
         .def("w", (float (osg::Vec4::*)() const) &osg::Vec4::w)
#endif
         .def("__setitem__", &__setitem__)


         .add_property("_x", get_x, set_x)
         .add_property("_y", get_y, set_y)
         .add_property("_z", get_z, set_z)
         .add_property("_w", get_w, set_w)

         .def("asABGR", &osg::Vec4::asABGR)
         .def("asRGBA", &osg::Vec4::asRGBA)

         .def("valid", &osg::Vec4::valid)
         .def("isNaN", &osg::Vec4::isNaN)

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

         .def("length", &osg::Vec4::length)
         .def("length2", &osg::Vec4::length2)
         .def("normalize", &osg::Vec4::normalize)

         .def("__str__", &osgVec4_str)
         .def("__repr__", &osgVec4_repr)
         ;
}
}
