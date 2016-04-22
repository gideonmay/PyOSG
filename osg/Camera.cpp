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


#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>

#include <osg/Camera>

#include "Group.hpp"

using namespace boost::python;

namespace {

}

namespace PyOSG {
    void init_Camera()
    {
        class_<osg::Camera, osg::ref_ptr<osg::Camera>,  bases<osg::Transform> > camera("Camera", no_init);

        camera
            .def(init<>())
            .def("setStats", &osg::Camera::setStats)
                .def("setAllowEventFocus", &osg::Camera::setAllowEventFocus)
                .def("setClearMask", &osg::Camera::setClearMask)
                .def("getClearMask", &osg::Camera::getClearMask)
                .def("setClearColor", &osg::Camera::setClearColor)
//                .def("getClearColor", &osg::Camera::getClearColor)
                .def("setClearAccum", &osg::Camera::setClearAccum)
//                .def("getClearAccum", &osg::Camera::getClearAccum)
                .def("setClearDepth", &osg::Camera::setClearDepth)
//                .def("getClearDepth", &osg::Camera::getClearDepth)
                .def("setClearStencil", &osg::Camera::setClearStencil)
//                .def("getClearStencil", &osg::Camera::getClearStencil)
//                .def("setColorMask", &osg::Camera::setColorMask)
                .def("setProjectionMatrixAsOrtho", &osg::Camera::setProjectionMatrixAsOrtho)
                .def("setProjectionMatrixAsOrtho2D", &osg::Camera::setProjectionMatrixAsOrtho2D)
                .def("setProjectionMatrixAsFrustum", &osg::Camera::setProjectionMatrixAsFrustum)
                .def("setProjectionMatrixAsPerspective", &osg::Camera::setProjectionMatrixAsPerspective)
                ;
    }
}