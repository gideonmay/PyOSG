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
            .def("realize",
                 &osgViewer::Viewer::realize)
            ;
}


} // namespace PyOSGViewer
