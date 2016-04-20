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
            .def("frame",
                 &osgViewer::ViewerBase::frame)
            .def("run",
                 &osgViewer::ViewerBase::run)
            .def("done",
                 &osgViewer::ViewerBase::done)
            .def("setThreadingModel",
                 &osgViewer::ViewerBase::setThreadingModel)
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
