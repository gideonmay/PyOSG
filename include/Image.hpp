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

#include <osg/Image>

#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

typedef class_<osg::Image, osg::ref_ptr<osg::Image>, bases<osg::Object>, boost::noncopyable > class_Image;
extern class_Image * ImageClass;      // Initialized in osg/Image.cpp

template <class F> void register_castImage(const char * name, F f)
{
    if (ImageClass) {
        ImageClass->def(name, f, return_value_policy<manage_osg_object>());
    }
}
}

#define DEFINE_IMAGE_CAST(NAME)    osg::NAME * as##NAME(osg::Image * self) { return dynamic_cast<osg::NAME *>(self); }
#define REGISTER_IMAGE_CAST(NAME)  register_castImage("as" #NAME, &as##NAME);

