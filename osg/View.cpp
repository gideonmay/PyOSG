//
// Created by gideon may on 20/04/16.
//

#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>

#include <osg/View>

#include "Group.hpp"

using namespace boost::python;

namespace {

}

namespace PyOSG {
    void init_View() {
        class_<osg::View, osg::ref_ptr<osg::View> > view("View", no_init);

        view
                .def(init<>());
    }
}
