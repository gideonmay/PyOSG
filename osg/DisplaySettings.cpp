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

#include <osg/DisplaySettings>

#include "held_ptr.hpp"

using namespace boost::python;

namespace {
osg::DisplaySettings * instance() { return osg::DisplaySettings::instance(); }
}

namespace PyOSG {
void init_DisplaySettings()
{
    class_<osg::DisplaySettings, osg::ref_ptr<osg::DisplaySettings>, bases<osg::Referenced> > settings("DisplaySettings", no_init);

    scope settings_scope(settings);

    settings
        .def(init<>())
        .def("readEnvironmentalVariables", &osg::DisplaySettings::readEnvironmentalVariables)
        .def("readCommandLine", (void (osg::DisplaySettings::*)(std::vector<std::string>&)) &osg::DisplaySettings::readCommandLine)

        .def("setDisplayType", &osg::DisplaySettings::setDisplayType)
        .def("getDisplayType", &osg::DisplaySettings::getDisplayType)

        .def("setStereo", &osg::DisplaySettings::setStereo)
        .def("getStereo", &osg::DisplaySettings::getStereo)

        .def("setStereoMode", &osg::DisplaySettings::setStereoMode)
        .def("getStereoMode", &osg::DisplaySettings::getStereoMode)

        .def("setEyeSeparation", &osg::DisplaySettings::setEyeSeparation)
        .def("getEyeSeparation", &osg::DisplaySettings::getEyeSeparation)

        .def("setScreenDistance", &osg::DisplaySettings::setScreenDistance)
        .def("getScreenDistance", &osg::DisplaySettings::getScreenDistance)

        .def("setSplitStereoHorizontalEyeMapping", &osg::DisplaySettings::setSplitStereoHorizontalEyeMapping)
        .def("getSplitStereoHorizontalEyeMapping", &osg::DisplaySettings::getSplitStereoHorizontalEyeMapping)

        .def("setSplitStereoHorizontalSeparation", &osg::DisplaySettings::setSplitStereoHorizontalSeparation)
        .def("getSplitStereoHorizontalSeparation", &osg::DisplaySettings::getSplitStereoHorizontalSeparation)

        .def("setSplitStereoVerticalEyeMapping", &osg::DisplaySettings::setSplitStereoVerticalEyeMapping)
        .def("getSplitStereoVerticalEyeMapping", &osg::DisplaySettings::getSplitStereoVerticalEyeMapping)

        .def("setSplitStereoVerticalSeparation", &osg::DisplaySettings::setSplitStereoVerticalSeparation)
        .def("getSplitStereoVerticalSeparation", &osg::DisplaySettings::getSplitStereoVerticalSeparation)

                // TODO : Missing ?
//        .def("setSplitStereoAutoAdjustAspectRatio", &osg::DisplaySettings::setSplitStereoAutoAjustAspectRatio)
//        .def("getSplitStereoAutoAdjustAspectRatio", &osg::DisplaySettings::getSplitStereoAutoAjustAspectRatio)

        .def("setScreenWidth", &osg::DisplaySettings::setScreenWidth)
        .def("getScreenWidth", &osg::DisplaySettings::getScreenWidth)

        .def("setScreenHeight", &osg::DisplaySettings::setScreenHeight)
        .def("getScreenHeight", &osg::DisplaySettings::getScreenHeight)

        .def("setScreenDistance", &osg::DisplaySettings::setScreenDistance)
        .def("getScreenDistance", &osg::DisplaySettings::getScreenDistance)

        .def("setDoubleBuffer", &osg::DisplaySettings::setDoubleBuffer)
        .def("getDoubleBuffer", &osg::DisplaySettings::getDoubleBuffer)

        .def("setRGB", &osg::DisplaySettings::setRGB)
        .def("getRGB", &osg::DisplaySettings::getRGB)

        .def("setDepthBuffer", &osg::DisplaySettings::setDepthBuffer)
        .def("getDepthBuffer", &osg::DisplaySettings::getDepthBuffer)

        .def("setMinimumNumAlphaBits", &osg::DisplaySettings::setMinimumNumAlphaBits)
        .def("getMinimumNumAlphaBits", &osg::DisplaySettings::getMinimumNumAlphaBits)
        .def("getAlphaBuffer", &osg::DisplaySettings::getAlphaBuffer)

        .def("setMinimumNumStencilBits", &osg::DisplaySettings::setMinimumNumStencilBits)
        .def("getMinimumNumStencilBits", &osg::DisplaySettings::getMinimumNumStencilBits)
        .def("getStencilBuffer", &osg::DisplaySettings::getStencilBuffer)

        .def("setMaxNumberOfGraphicsContexts", &osg::DisplaySettings::setMaxNumberOfGraphicsContexts)
        .def("getMaxNumberOfGraphicsContexts", &osg::DisplaySettings::getMaxNumberOfGraphicsContexts)
        .def("instance",
            &instance,
            return_value_policy<reference_existing_object>())
        .staticmethod("instance")

        ;

#   define OSG_ENUM_DTYPE(VALUE) dtype.value(#VALUE, osg::DisplaySettings::VALUE)
    enum_<osg::DisplaySettings::DisplayType> dtype("DisplayType");
    OSG_ENUM_DTYPE(MONITOR);
    OSG_ENUM_DTYPE(POWERWALL);
    OSG_ENUM_DTYPE(REALITY_CENTER);
    OSG_ENUM_DTYPE(HEAD_MOUNTED_DISPLAY);
    dtype.export_values();

    enum_<osg::DisplaySettings::StereoMode> smode("StereoMode");
#   define OSG_ENUM_SMODE(VALUE) smode.value(#VALUE, osg::DisplaySettings::VALUE)
    OSG_ENUM_SMODE(QUAD_BUFFER);
    OSG_ENUM_SMODE(ANAGLYPHIC);
    OSG_ENUM_SMODE(HORIZONTAL_SPLIT);
    OSG_ENUM_SMODE(VERTICAL_SPLIT);
    OSG_ENUM_SMODE(LEFT_EYE);
    OSG_ENUM_SMODE(RIGHT_EYE);
    smode.export_values();

#   define OSG_ENUM_HMAPPING(VALUE) hmapping.value(#VALUE, osg::DisplaySettings::VALUE)
    enum_<osg::DisplaySettings::SplitStereoHorizontalEyeMapping> hmapping("SplitStereoHorizontalEyeMapping");
    OSG_ENUM_HMAPPING(LEFT_EYE_LEFT_VIEWPORT);
    OSG_ENUM_HMAPPING(LEFT_EYE_RIGHT_VIEWPORT);
    hmapping.export_values();

#   define OSG_ENUM_VMAPPING(VALUE) vmapping.value(#VALUE, osg::DisplaySettings::VALUE)
    enum_<osg::DisplaySettings::SplitStereoVerticalEyeMapping> vmapping("SplitStereoVerticalEyeMapping");
    OSG_ENUM_VMAPPING(LEFT_EYE_TOP_VIEWPORT);
    OSG_ENUM_VMAPPING(LEFT_EYE_BOTTOM_VIEWPORT);
    vmapping.export_values();
}
} // namespace
