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
