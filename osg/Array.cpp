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

#include <osg/Array>

#include "held_ptr.hpp"
#include "Math.hpp"

using namespace boost::python;

namespace PyOSG {

// Construct a osg::Array from a python tuple.
// Depending on the element type of tuple[0], 
// either a UInt, Vec2, Vec3 or Vec4 array will be
// created.
osg::ref_ptr<osg::Array> toArray(const boost::python::tuple& vertlist)
{
    osg::ref_ptr<osg::Array> array;

    ssize_t elements = len(vertlist);
    if (elements == 0) return array;

    // Determine the type of array depending on the first element.
    ssize_t elsize = 0;

    const object& el = vertlist[0];
    if (check_tuple(el)) {
        elsize = len(el);
    } else {
        elsize = 1;
    }

    try {
        switch (elsize) {
            case 1:
                {
                osg::ref_ptr<osg::UIntArray> coords = new osg::UIntArray;
                array = coords.get();
                coords->resize(elements);
                for (int i=0; i<elements ; i++) {
                    (*coords)[i] = extract<unsigned int>(vertlist[i]);
                }
                }
                break;
            case 2:
                {
                osg::ref_ptr<osg::Vec2Array> coords = new osg::Vec2Array;
                array = coords.get();
                coords->resize(elements);
                for (int i=0; i<elements ; i++) {
                    const tuple& vertex = extract<tuple>(vertlist[i]);
                    (*coords)[i].set(extract<float>(vertex[0]),
                                     extract<float>(vertex[1]));
                }
                }
                break;
            case 3:
                {
                osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
                array = coords.get();
                coords->resize(elements);
                for (int i=0; i<elements ; i++) {
                    const tuple& vertex = extract<tuple>(vertlist[i]);
                    (*coords)[i].set(extract<float>(vertex[0]),
                                     extract<float>(vertex[1]),
                                     extract<float>(vertex[2]));
                }
                }
                break;
            case 4:
                {
                osg::ref_ptr<osg::Vec4Array> coords = new osg::Vec4Array;
                array = coords.get();
                coords->resize(elements);
                for (int i=0; i<elements ; i++) {
                    const tuple& vertex = extract<tuple>(vertlist[i]);
                    (*coords)[i].set(extract<float>(vertex[0]),
                                     extract<float>(vertex[1]),
                                     extract<float>(vertex[2]),
                                     extract<float>(vertex[3]));
                }
                }
                break;
            default:
                PyErr_SetString(PyExc_ValueError, "Unexpected element size in array");
                throw_error_already_set();
                break;
        }
    } catch(...) {
        PyErr_SetString(PyExc_ValueError, "Unexpected element type in array");
        throw_error_already_set();
    }

    return array;
}


void init_Array()
{
    class_<osg::Array, osg::ref_ptr<osg::Array>, bases<osg::Object>, boost::noncopyable> array("Array", no_init);
    {
        scope array_scope(array);
        array.def("getType",          &osg::Array::getType)
             .def("getDataSize",      &osg::Array::getDataSize)
             .def("getDataType",      &osg::Array::getDataType)
             .def("getTotalDataSize", &osg::Array::getTotalDataSize)
             .def("getNumElements",   &osg::Array::getNumElements)
             ;

#       define OSG_ENUM(VALUE) _type.value(#VALUE, osg::Array::VALUE)
        enum_<osg::Array::Type> _type("Type");
        OSG_ENUM(ArrayType);
        OSG_ENUM(ByteArrayType);
        OSG_ENUM(ShortArrayType);
        OSG_ENUM(IntArrayType);
        OSG_ENUM(UByteArrayType);
        OSG_ENUM(UShortArrayType);
        OSG_ENUM(UIntArrayType);
        OSG_ENUM(Vec4ubArrayType);
        OSG_ENUM(FloatArrayType);
        OSG_ENUM(Vec2ArrayType);
        OSG_ENUM(Vec3ArrayType);
        OSG_ENUM(Vec4ArrayType);
        OSG_ENUM(Vec2sArrayType);
        OSG_ENUM(Vec3sArrayType);
        OSG_ENUM(Vec4sArrayType);
        OSG_ENUM(Vec2bArrayType);
        OSG_ENUM(Vec3bArrayType);
        OSG_ENUM(Vec4bArrayType);
        _type.export_values();
#       undef OSG_ENUM
    }

    class_<osg::IndexArray, osg::ref_ptr<osg::IndexArray>, bases<osg::Array>, boost::noncopyable> indexArray("IndexArray", no_init);
}
}

