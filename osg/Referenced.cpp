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

#include <iostream>
#include <boost/python.hpp>

#include <osg/Referenced>

#include "held_ptr.hpp"

using namespace boost::python;

namespace {

// Return the demangled typename of a given reference object
// Somehow human readable, depending on platform

std::string typeName(osg::Referenced * ref)
{
    std::ostringstream ost;
    ost << typeid(*ref).name();
    return ost.str();
}

// Return a unique Identifier for a reference object
long ref_getId(osg::Referenced * ref)
{
    return (long) ref;
}

// Used in python object comparison
int ref_cmp(osg::Referenced * self, osg::Referenced * other)
{
    if (self == other) return 0;
    if (self < other) return -1;
    return 1;
}


// Used in python object comparison
long ref_hash(osg::Referenced * self)
{
    return (long) self;
}
} // namespace


namespace PyOSG {
void init_Referenced()
{
    class_<osg::Referenced, osg::ref_ptr<osg::Referenced>, boost::noncopyable>("Referenced", no_init)
         .def("ref", &osg::Referenced::ref)
         .def("unref", &osg::Referenced::unref)
         .def("unref_nodelete", &osg::Referenced::unref_nodelete)
         .def("referenceCount", &osg::Referenced::referenceCount)
         .def("typeName", &typeName)
         .def("getId", &ref_getId)
         .def("__cmp__", &ref_cmp)
         .def("__hash__", &ref_hash)
         ;
}
}

