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
