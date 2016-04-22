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



#include <boost/python.hpp>

#include <string>
#include <iostream>

#include <osg/Timer>
using namespace boost::python;

class Timer : public osg::Timer {
  private:
    int dummy_;
};

Timer& instance()
{
    // XXX Danger Will Robinson, a static cast due to compiler error
    // in Apple gcc 3.3
    Timer * timer = (Timer*) const_cast<osg::Timer*>(osg::Timer::instance());
    return * timer;
}

namespace PyOSG {
void init_Timer()
{
    class_<Timer>("Timer",
        "A high resolution, low latency time stamper.")
        .def("tick", &Timer::tick)
        .def("delta_s", &Timer::delta_s)
        .def("delta_m", &Timer::delta_m)
        .def("delta_u", &Timer::delta_u)
        .def("delta_n", &Timer::delta_n)
        .def("getSecondsPerTick", &Timer::getSecondsPerTick)
        .def("instance", 
                &instance,
                return_value_policy<copy_non_const_reference>()
                )
        .staticmethod("instance")
        ;
}
}
