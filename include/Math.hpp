#ifndef PYOSG_MATH
#define PYOSG_MATH 1

#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>

#include <osg/Array>

namespace PyOSG {
osg::ref_ptr<osg::Array> toArray(const boost::python::tuple& vertices);

inline bool check_tuple(boost::python::object x) { return boost::python::extract<boost::python::tuple>(x).check(); }
inline bool check_Array(boost::python::object x) { return boost::python::extract<osg::Array *>(x).check(); }
inline bool check_Vec3Array(boost::python::object x) { return boost::python::extract<osg::Vec3Array *>(x).check(); }
}

#endif // PYOSG_MATH
