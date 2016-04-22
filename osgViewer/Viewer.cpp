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
#include <osgViewer/Viewer>

using namespace boost::python;

namespace {
}

namespace PyOSGViewer {

void init_Viewer()
{
    class_<osgViewer::Viewer, osg::ref_ptr<osgViewer::Viewer>, bases< osgViewer::View, osgViewer::ViewerBase >, boost::noncopyable > viewer("Viewer", no_init);

    scope viewer_scope(viewer);

    viewer
            .def(init<>())
            .def("readConfiguration",
                 &osgViewer::Viewer::readConfiguration)

            .def("isRealized",
                 &osgViewer::Viewer::isRealized)

            .def("realize",
                 &osgViewer::Viewer::realize)

            .def("setStartTick",
                 &osgViewer::Viewer::setStartTick)
            .def("setReferenceTime",
                 &osgViewer::Viewer::setReferenceTime)

            .def("setSceneData",
                 &osgViewer::Viewer::setSceneData)

            .def("elapsedTime",
                 &osgViewer::Viewer::elapsedTime)

//            .def("getViewerFrameStamp",
//                 &osgViewer::Viewer::getViewerFrameStamp)

            .def("advance",
                 &osgViewer::Viewer::advance)
            ;
}


} // namespace PyOSGViewer
