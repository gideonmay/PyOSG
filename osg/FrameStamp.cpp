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

#include <osg/FrameStamp>

#include "held_ptr.hpp"

using namespace boost::python;

namespace PyOSG {
void init_FrameStamp()
{
    class_<osg::FrameStamp, osg::ref_ptr<osg::FrameStamp>, bases<osg::Referenced> > 
        framestamp("FrameStamp", 
            "Class which encapsulates the frame number, reference time and calander\n"
            "time of specific frame, used to synchonize operations on the scene graph\n"
            "and other machines when using a graphics cluster.  Note the calander\n"
            "time can be an artificial simulation time or capture the real time\n"
            "of day etc.\n",
            no_init);

    framestamp
        .def(init<>())

        .def("setFrameNumber",
            &osg::FrameStamp::setFrameNumber)

        .def("getFrameNumber",
            &osg::FrameStamp::getFrameNumber)

        .def("setReferenceTime",
            &osg::FrameStamp::setReferenceTime)

        .def("getReferenceTime",
            &osg::FrameStamp::getReferenceTime)

        .def("setCalendarTime",
            &osg::FrameStamp::setCalendarTime)

        .def("getCalendarTime",
            &osg::FrameStamp::getCalendarTime)

        ;

}
}

