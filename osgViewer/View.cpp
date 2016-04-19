//
// Created by gideon may on 19/04/16.
//

#include <boost/python.hpp>
#include <osgViewer/View>

using namespace boost::python;

namespace {
    void setSceneData(osgViewer::View & view, osg::Node * node) {
        view.setSceneData(node);
    }
    void setCameraManipulator_1(osgViewer::View &view, osgGA::CameraManipulator* manipulator)
    {
        view.setCameraManipulator(manipulator);
    }
    void setCameraManipulator_2(osgViewer::View &view, osgGA::CameraManipulator* manipulator, bool resetPosition)
    {
        view.setCameraManipulator(manipulator, resetPosition);
    }

    void setUpViewInWindow_1(osgViewer::View &view, int x, int y, int width, int height, unsigned int screenNum)
    {
        view.setUpViewInWindow(x, y, width, height, screenNum);
    }
    void setUpViewInWindow_2(osgViewer::View &view, int x, int y, int width, int height)
    {
        view.setUpViewInWindow(x, y, width, height);
    }
}

namespace PyOSGViewer {

    void init_View()
    {
        class_<osgViewer::View, osg::ref_ptr<osgViewer::View>, bases<osgViewer::ViewerBase>, boost::noncopyable > view("View", no_init);

        scope viewer_scope(view);

        view
                .def(init<>())
                .def("setSceneData",
                     &setSceneData)
                .def("setCameraManipulator",
                     &setCameraManipulator_1)
                .def("setCameraManipulator",
                     &setCameraManipulator_2)
                .def("setUpViewInWindow",                // Deprecated
                    &setUpViewInWindow_1)
                .def("setUpViewInWindow",                // Deprecated
                     &setUpViewInWindow_2)
                ;
    }


} // namespace PyOSGViewer
