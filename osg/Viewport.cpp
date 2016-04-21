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
#include <boost/python/implicit.hpp>
#include <boost/python/tuple.hpp>

#include <string>
#include <iostream>
#include <sstream>

#include <osg/Viewport>

#include "StateAttribute.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
osg::Viewport * asViewport(osg::StateAttribute * self) { return dynamic_cast<osg::Viewport*>(self); }

#if 0 // Deprecated
tuple getViewport(osg::Viewport * self)
{
    int x, y, w, h;

    self->getViewport(x, y, w, h);
    return make_tuple(x, y, w, h);
}
#endif


int getX(osg::Viewport *self)
{
   return self->x();
}

int getY(osg::Viewport *self)
{
   return self->y();
}

int getWidth(osg::Viewport *self)
{
   return self->width();
}

int getHeight(osg::Viewport *self)
{
   return self->height();
}

std::string repr(osg::Viewport * self)
{
    std::ostringstream ost;
    ost << "Viewport(" << self->x() << "," << self->y() << "," << self->width() << "," << self->height() << ")";
    return ost.str();
}

std::string str(osg::Viewport * self)
{
    std::ostringstream ost;
    ost << "(" << self->x() << "," << self->y() << "," << self->width() << "," << self->height() << ")";
    return ost.str();
}

} // namespace

namespace PyOSG {
void init_Viewport()
{
    register_castStateAttribute("asViewport", &asViewport);

    class_<osg::Viewport, osg::ref_ptr<osg::Viewport>, bases<osg::StateAttribute> >("Viewport", no_init)
        .def(init<>())

        .def("setViewport", &osg::Viewport::setViewport)
        // .def("getViewport", &getViewport)
        .def("x", &getX)
        .def("y", &getY)
        .def("width", &getWidth)
        .def("height", &getHeight)
        .def("valid", &osg::Viewport::valid)

        .def("aspectRatio", &osg::Viewport::aspectRatio,
            "Return the aspcetRatio of the viewport, which is equal to width/height.\n"
            "If height is zero, the potental division by zero is avoid by simply returning 1.0f.\n"
            )

        .def("computeWindowMatrix", &osg::Viewport::computeWindowMatrix,
            "Compute the Window Matrix which takes projected coords into Window coordinates.\n"
            "To converted local coodinates into window coordinates use v_window = v_local * MVPW matrix, \n"
            "where the MVPW matrix is ModelViewMatrix * ProjectionMatrix * WindowMatrix, the later supplied by \n"
            "viewport::computeWindowMatrix(), the ModelView and Projection Matrix can either be sourced from the\n"
            "current osg::State object, via osgUtil::SceneView or CullVisitor.\n"
            )
        .def("__str__", &str)
        .def("__repr__", &repr)
        ;

}
} // namespace PyOSG
