//
// Created by gideon may on 19/04/16.
//

#ifdef __USE_OSX_IMPLEMENTATION__
#include <strings.h>
#include "missing.hpp"
#include <Carbon/Carbon.h>
#undef check
#endif

#include <boost/python.hpp>

#include <osgViewer/ViewerEventHandlers>
#include <iostream>

using namespace boost::python;

namespace {
}

namespace PyOSGViewer {

void init_ViewerEventHandlers() {

    class_<osgViewer::ScreenCaptureHandler::CaptureOperation,
            osg::ref_ptr<osgViewer::ScreenCaptureHandler::CaptureOperation>,
            boost::noncopyable >
            capture_operation("CaptureOperation", no_init);


    class_<osgViewer::ScreenCaptureHandler::WriteToFile,
            osg::ref_ptr<osgViewer::ScreenCaptureHandler::WriteToFile>,
            bases<osgViewer::ScreenCaptureHandler::CaptureOperation>,
            boost::noncopyable >

            write_to_file("WriteToFile", no_init);
    write_to_file
            .def(init<const std::string&, const std::string&>())
            ;

    class_<osgViewer::ScreenCaptureHandler,  boost::noncopyable >
            screen_capture_handler("ScreenCaptureHandler", no_init);

    scope screen_capture_handler_scope(screen_capture_handler);

    screen_capture_handler
            .def(init<>())
            .def("setCaptureOperation",
                 &osgViewer::ScreenCaptureHandler::setCaptureOperation)
            .def("captureNextFrame",
                 &osgViewer::ScreenCaptureHandler::captureNextFrame
            );
}

}