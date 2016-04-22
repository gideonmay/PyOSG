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

#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <signal.h>
#include <string>

#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/UFOManipulator>
#include <iostream>

#include "held_ptr.hpp"

using namespace boost::python;

#if 0
typedef osgGA::MatrixManipulator    osgGA_MatrixManipulator;

class MatrixManipulator_callback : public osgGA::MatrixManipulator {
  public:
    MatrixManipulator_callback() {}
    ~MatrixManipulator_callback() {}

    void setNode_imp(osg::Node * node) 
    {
        this->osgGA_MatrixManipulator::setNode(node);
    }
    const osg::Node * getNode_imp() const 
    {
        return this->osgGA_MatrixManipulator::getNode();
    }
    void home_imp(osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
    {
        this->osgGA_MatrixManipulator::home(ea, us);
    }
    void init_imp(osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
    {
        this->osgGA_MatrixManipulator::init(ea, us);
    }
    bool handle_imp(osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
    {
        return this->osgGA_MatrixManipulator::handle(ea, us);
    }
};
#endif

namespace PyOSG {
    void init_GUIActionAdapter();
    void init_GUIEventAdapter();
    void init_GUIEventHandler();
    void init_MatrixManipulator();

void __init_osgGA()
{
    init_GUIActionAdapter();
    init_GUIEventAdapter();
    init_GUIEventHandler();
    init_MatrixManipulator();


#if 0
    class_<osgGA::CameraManipulator, osg::ref_ptr<osgGA::CameraManipulator>, bases<osgGA::GUIEventHandler>, boost::noncopyable>("CameraManipulator", no_init)
            .def(init<>())
            ;
#else
    class_<osgGA::CameraManipulator, osg::ref_ptr<osgGA::CameraManipulator>, boost::noncopyable>("CameraManipulator", no_init)
            ;
#endif

    class_<osgGA::StandardManipulator, osg::ref_ptr<osgGA::StandardManipulator>, bases<osgGA::CameraManipulator>, boost::noncopyable>("StandardManipulator", no_init)
            ;

    class_<osgGA::OrbitManipulator, osg::ref_ptr<osgGA::OrbitManipulator>, bases<osgGA::StandardManipulator>, boost::noncopyable>("OrbitManipulator", no_init)
            .def(init<>())
            ;

    class_<osgGA::TrackballManipulator, osg::ref_ptr<osgGA::TrackballManipulator>, bases<osgGA::OrbitManipulator>, boost::noncopyable>("TrackballManipulator", no_init)
            .def(init<>())
            ;

#if 0
    class_<osgGA::GUIEventHandlerVisitor, boost::noncopyable>("GUIEventHandlerVisitor", no_init)
        ;

    class_<osgGA::DriveManipulator, osg::ref_ptr<osgGA::DriveManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("DriveManipulator", no_init)
        .def(init<>())
        ;

    class_<osgGA::FlightManipulator, osg::ref_ptr<osgGA::FlightManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("FlightManipulator", no_init)
        .def(init<>())
        ;

    class_<osgGA::KeySwitchMatrixManipulator, osg::ref_ptr<osgGA::KeySwitchMatrixManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("KeySwitchMatrixManipulator", no_init)
        .def(init<>())
        ;

    class_<osgGA::NodeTrackerManipulator, osg::ref_ptr<osgGA::NodeTrackerManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("NodeTrackerManipulator", no_init)
        .def(init<>())
        ;

    class_<osgGA::TerrainManipulator, osg::ref_ptr<osgGA::TerrainManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("TerrainManipulator", no_init)
        .def(init<>())
        ;

    class_<osgGA::UFOManipulator, osg::ref_ptr<osgGA::UFOManipulator>, bases<osgGA::MatrixManipulator>, boost::noncopyable>("UFOManipulator", no_init)
        .def(init<>())
        ;
#endif

}
}

BOOST_PYTHON_MODULE(_osgGA)
{
    scope().attr("__doc__") = "Wrapper for the OpenSceneGraph dbase scene graph library\n";
    PyOSG::__init_osgGA();
}
#include "module_tail.hpp"
