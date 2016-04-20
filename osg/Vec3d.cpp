#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/copy_non_const_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/detail/api_placeholder.hpp>

#include <osg/Vec3f>
#include <osg/Vec3d>

#include <string>
#include <iostream>
#include <sstream>

using namespace boost::python;

namespace {

osg::Vec3d* vec3tuple(tuple data)
{
    double x = 0, y = 0, z = 0;

    // Fall through intentionally!
    switch (len(data)) {
        case 3: z = extract<double>(data[2]);
        case 2: y = extract<double>(data[1]);
        case 1: x = extract<double>(data[0]);
    }
    return new osg::Vec3d(x, y, z);
}

std::string vec3_repr(osg::Vec3d * self)
{
    std::ostringstream ost;
    ost << "Vec3d(" << self->_v[0] << "," << self->_v[1] << "," << self->_v[2] << ")";
    return ost.str();
}

std::string vec3_str(osg::Vec3d * self)
{
    std::ostringstream ost;
    ost << self->_v[0] << " " << self->_v[1] << " " << self->_v[2];
    return ost.str();
}

inline void set(osg::Vec3d * self, osg::Vec3d& from) { * self = from; }

inline void __setitem__(osg::Vec3d * self, int idx, double val) { (*self)[idx] = val; }

inline double get_x(osg::Vec3d * self) { return self->_v[0]; }
inline void  set_x(osg::Vec3d * self, double x) { self->_v[0] = x; }

inline double get_y(osg::Vec3d * self) { return self->_v[1]; }
inline void  set_y(osg::Vec3d * self, double y) { self->_v[1] = y; }

inline double get_z(osg::Vec3d * self) { return self->_v[2]; }
inline void  set_z(osg::Vec3d * self, double z) { self->_v[2] = z; }

} // namespace

namespace PyOSG {
void init_Vec3d()
{
    class_<osg::Vec3d> vec3("Vec3d",
        "General purpose double triple for use as vertices, vectors and normals.\n"
        "Provides general maths operations from addition through to cross products.\n"
        "No support yet added for double * Vec3d - is it necessary?\n"
        "Need to define a non-member non-friend operator*  etc.\n"
        " Vec3d * double is okay\n");

     vec3
         .def(init<double, double, double>())
         .def(init<const osg::Vec3f& >())
         .def("__init__", make_constructor(vec3tuple))
         .def(self == self)
         .def(self != self)
         .def(self < self)
         // .def("set", (void (osg::Vec3d::*)(double, double, double)) &osg::Vec3d::set)
         .def("set", &set)
         // .def("__getitem__", (double &(osg::Vec3d::*)(int)) &osg::Vec3d::operator[], return_value_policy<copy_non_const_reference>())
         .def("__setitem__", &__setitem__)
         // .def("x", (double (osg::Vec3d::*)() const) &osg::Vec3d::x)
         // .def("y", (double (osg::Vec3d::*)() const) &osg::Vec3d::y)
         // .def("z", (double (osg::Vec3d::*)() const) &osg::Vec3d::z)
         .add_property("_x", get_x, set_x)
         .add_property("_y", get_y, set_y)
         .add_property("_z", get_z, set_z)
         .def("valid", &osg::Vec3d::valid)
         .def("isNaN", &osg::Vec3d::isNaN)

         .def(self * self)
         .def(self ^ self)
         .def(self * double())
         .def(self *= double())
         .def(self / double())
         .def(self /= double())
         .def(self + self)
         .def(self += self)
         .def(self - self)
         .def(self -= self)
         .def(-self)

         .def("length", &osg::Vec3d::length,
            "Length of the vector = sqrt( vec . vec )\n")
         .def("length2", &osg::Vec3d::length2,
            "Length squared of the vector = vec . vec\n")
         .def("normalize", &osg::Vec3d::normalize,
            "normalize the vector so that it has length unity\n"
            "returns the previous length of the vector*/\n")

         .def("__str__", &vec3_str)
         .def("__repr__", &vec3_repr)

         ;

    implicitly_convertible<osg::Vec3d, osg::Vec3f>();
    implicitly_convertible<osg::Vec3f, osg::Vec3d>();

    scope().attr("X_AXIS") = osg::X_AXIS;
    scope().attr("Y_AXIS") = osg::Y_AXIS;
    scope().attr("Z_AXIS") = osg::Z_AXIS;
}
}
