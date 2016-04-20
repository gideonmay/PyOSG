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

