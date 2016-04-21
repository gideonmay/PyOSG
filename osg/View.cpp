//
// Created by gideon may on 20/04/16.
//

#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>

#include <osg/Light>
#include <osg/View>

using namespace boost::python;

namespace {

}

namespace PyOSG {
    void init_View() {
        class_<osg::View, osg::ref_ptr<osg::View>, bases<osg::Object> > view("View", no_init);

        view
            .def(init<>())
            .def("setLightingMode", &osg::View::setLightingMode)
            .def("getLightingMode", &osg::View::getLightingMode)
                .def("setLight", &osg::View::setLight)
//                .def("getLight", (osg::Light * (osg::View::*)(void)) &osg::View::getLight)
                .def("setCamera", &osg::View::setCamera)
                .def("setFrameStamp", &osg::View::setFrameStamp)
        ;
    }
}
