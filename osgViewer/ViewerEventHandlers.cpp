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
            bases <osg::Referenced>,
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
