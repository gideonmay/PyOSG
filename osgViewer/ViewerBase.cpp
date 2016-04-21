#include <boost/python.hpp>

#include <osgViewer/Viewer>

using namespace boost::python;

namespace {
}

namespace PyOSGViewer {

void init_ViewerBase()
{
    class_<osgViewer::ViewerBase, osg::ref_ptr<osgViewer::ViewerBase>, bases<osg::Object>, boost::noncopyable > viewer_base("ViewerBase", no_init);

    scope viewer_base_scope(viewer_base);

    viewer_base

            .def("setThreadingModel",
                 &osgViewer::ViewerBase::setThreadingModel)
            .def("getThreadingModel",
                 &osgViewer::ViewerBase::getThreadingModel)
            .def("suggestBestThreadingModel",
                 &osgViewer::ViewerBase::suggestBestThreadingModel)
            .def("setUpThreading",
                 &osgViewer::ViewerBase::setUpThreading)
            .def("areThreadsRunning",
                 &osgViewer::ViewerBase::areThreadsRunning)
            .def("stopThreading",
                 &osgViewer::ViewerBase::stopThreading)
            .def("startThreading",
                 &osgViewer::ViewerBase::startThreading)

            .def("setDone",
                 &osgViewer::ViewerBase::setDone)
            .def("done",
                 &osgViewer::ViewerBase::done)

            .def("run",
                 &osgViewer::ViewerBase::run)

            .def("advance",
                 &osgViewer::ViewerBase::advance)
            .def("frame",
                 &osgViewer::ViewerBase::frame)
            ;

#   define OSG_ENUM(VALUE) tmodel.value(#VALUE, osgViewer::ViewerBase::VALUE)
    enum_<osgViewer::ViewerBase::ThreadingModel> tmodel("ThreadingModel");

    OSG_ENUM(SingleThreaded);
    OSG_ENUM(CullDrawThreadPerContext);
    OSG_ENUM(ThreadPerContext);
    OSG_ENUM(DrawThreadPerContext);
    OSG_ENUM(CullThreadPerCameraDrawThreadPerContext);
    OSG_ENUM(ThreadPerCamera);
    OSG_ENUM(AutomaticSelection);

    tmodel.export_values();

}
} // namespace PyOSGViewer
