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

#include <osg/Notify>
#include <string>

using namespace boost::python;

void notify_1(osg::NotifySeverity severity, std::string str)
{
    osg::notify(severity) << str;
}

void notify_2(std::string str)
{
    osg::notify() << str;
}

namespace PyOSG {
void init_Notify()
{
    def("setNotifyLevel", &osg::setNotifyLevel);
    def("getNotifyLevel", &osg::getNotifyLevel);
    def("initNotifyLevel", &osg::initNotifyLevel);
    def("isNotifyEnabled", &osg::isNotifyEnabled);
    def("notify", &notify_1);
    def("notify", &notify_2);

#   define OSG_ENUM_NOTIFY_SEVERITY(VALUE) severity.value(#VALUE, osg::VALUE)
    enum_<osg::NotifySeverity> severity("NotifySeverity");
    OSG_ENUM_NOTIFY_SEVERITY(ALWAYS);
    OSG_ENUM_NOTIFY_SEVERITY(FATAL);
    OSG_ENUM_NOTIFY_SEVERITY(WARN);
    OSG_ENUM_NOTIFY_SEVERITY(NOTICE);
    OSG_ENUM_NOTIFY_SEVERITY(INFO);
    OSG_ENUM_NOTIFY_SEVERITY(DEBUG_INFO);
    OSG_ENUM_NOTIFY_SEVERITY(DEBUG_FP);
    severity.export_values();
}
} // namespace
