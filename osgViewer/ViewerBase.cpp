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
            ;
}
} // namespace PyOSGViewer
