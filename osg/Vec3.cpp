#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/detail/api_placeholder.hpp>

#include <osg/Vec3>
#include <osg/Vec3d>

#include <string>
#include <iostream>
#include <sstream>

using namespace boost::python;

namespace {

osg::Vec3* vec3tuple(tuple data)
{
    float x = 0, y = 0, z = 0;

    // Fall through intentionally!
    switch (len(data)) {
        case 3: z = extract<float>(data[2]);
        case 2: y = extract<float>(data[1]);
        case 1: x = extract<float>(data[0]);
    }
    return new osg::Vec3(x, y, z);
}

std::string vec3_repr(osg::Vec3 * self)
{
    std::ostringstream ost;
    ost << "Vec3(" << self->_v[0] << "," << self->_v[1] << "," << self->_v[2] << ")";
    return ost.str();
}

std::string vec3_str(osg::Vec3 * self)
{
    std::ostringstream ost;
    ost << "(" << self->_v[0] << " " << self->_v[1] << " " << self->_v[2] << ")";
    return ost.str();
}

#ifdef WIN32
inline void set_floats(osg::Vec3 * self, float x, float y, float z) { self->set(x, y, z); }
#endif
inline void set(osg::Vec3 * self, osg::Vec3& from) { * self = from; }

inline void __setitem__(osg::Vec3 * self, int idx, float val) { (*self)[idx] = val; }
inline float __getitem__(osg::Vec3 * self, int idx) { return (*self)[idx]; }

inline float get_x(osg::Vec3 * self) { return self->_v[0]; }
inline void  set_x(osg::Vec3 * self, float x) { self->_v[0] = x; }

inline float get_y(osg::Vec3 * self) { return self->_v[1]; }
inline void  set_y(osg::Vec3 * self, float y) { self->_v[1] = y; }

inline float get_z(osg::Vec3 * self) { return self->_v[2]; }
inline void  set_z(osg::Vec3 * self, float z) { self->_v[2] = z; }

} // namespace

namespace PyOSG {
void init_Vec3()
{
    class_<osg::Vec3> vec3("Vec3",
        "General purpose float triple for use as vertices, vectors and normals.\n"
        "Provides general maths operations from addition through to cross products.\n"
        "No support yet added for float * Vec3 - is it necessary?\n"
        "Need to define a non-member non-friend operator*  etc.\n"
        " Vec3 * float is okay\n");

     vec3
         .def(init<float, float, float>())
         .def(init<const osg::Vec3& >())
         .def("__init__", make_constructor(vec3tuple))
         .def(self == self)
         .def(self != self)
         .def(self < self)
         .def("set", &set)
         .def("__setitem__", &__setitem__)
#ifdef WIN32
         .def("set", set_floats)
         .def("__getitem__", &__getitem__)
         .def("x", get_x)
         .def("y", get_y)
         .def("z", get_z)
#else
         .def("set", (void (osg::Vec3::*)(float, float, float)) &osg::Vec3::set)
         .def("__getitem__", (float &(osg::Vec3::*)(int)) &osg::Vec3::operator[], return_value_policy<copy_non_const_reference>())
         .def("x", (float (osg::Vec3::*)() const) &osg::Vec3::x)
         .def("y", (float (osg::Vec3::*)() const) &osg::Vec3::y)
         .def("z", (float (osg::Vec3::*)() const) &osg::Vec3::z)
#endif
         .add_property("_x", get_x, set_x)
         .add_property("_y", get_y, set_y)
         .add_property("_z", get_z, set_z)
         .def("valid", &osg::Vec3::valid)
         .def("isNaN", &osg::Vec3::isNaN)

         .def(self * self)
         .def(self ^ self)
         .def(self * float())
         .def(self *= float())
         .def(self / float())
         .def(self /= float())
         .def(self + self)
         .def(self += self)
         .def(self - self)
         .def(self -= self)
         .def(-self)

         .def("length", &osg::Vec3::length,
            "Length of the vector = sqrt( vec . vec )\n")
         .def("length2", &osg::Vec3::length2,
            "Length squared of the vector = vec . vec\n")
         .def("normalize", &osg::Vec3::normalize,
            "normalize the vector so that it has length unity\n"
            "returns the previous length of the vector*/\n")

         .def("__str__", &vec3_str)
         .def("__repr__", &vec3_repr)
         ;

    scope().attr("X_AXIS") = osg::X_AXIS;
    scope().attr("Y_AXIS") = osg::Y_AXIS;
    scope().attr("Z_AXIS") = osg::Z_AXIS;
}
}
