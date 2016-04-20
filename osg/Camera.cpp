//
// Created by gideon may on 20/04/16.
//

#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>

#include <osg/Camera>

#include "Group.hpp"

using namespace boost::python;

namespace {

}

namespace PyOSG {
    void init_Camera()
    {
        class_<osg::Camera, osg::ref_ptr<osg::Camera> > camera("Camera", no_init);

        camera
            .def(init<>())
                ;
    }
}