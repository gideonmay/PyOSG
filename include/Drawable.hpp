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

#ifndef  PYOSG_DRAWABLE
#define  PYOSG_DRAWABLE 1

#include <osg/Drawable>

#include <boost/python/class.hpp>
#include <boost/python/return_internal_reference.hpp>

#include "held_ptr.hpp"

namespace PyOSG {
using namespace boost::python;

class Drawable_callback;

typedef class_<osg::Drawable, osg::ref_ptr<osg::Drawable>, bases<osg::Object>, boost::noncopyable > class_Drawable;
// typedef class_<osg::Drawable, osg::ref_ptr<Drawable_callback>, bases<osg::Object>, boost::noncopyable > class_Drawable;
extern class_Drawable * DrawableClass;

template <class F> void register_castDrawable(const char * name, F f)
{
    if (DrawableClass) {
        DrawableClass->def(name, f, boost::python::return_internal_reference<>());
    }
}
}

#endif
