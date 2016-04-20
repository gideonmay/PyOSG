#include <boost/python/class.hpp>
#include <boost/python/call_method.hpp>

#include <osgUtil/SceneView>
#include <osgGA/GUIEventHandler>
#include <osgGA/CameraManipulator>

#include "held_ptr.hpp"

using namespace boost::python;

namespace {

class CameraManipulator : public osgGA::CameraManipulator {
  public:
    CameraManipulator(PyObject * self) : osgGA::CameraManipulator(), _self(self)
    {
        // std::cerr << "osgGA::CameraManipulator()\n";
        // ref();
    }


    ~CameraManipulator() {
        // std::cerr << "~osgGA::CameraManipulator()\n";
        // unref();
    }

    /** set the position of the matrix manipulator using a 4x4 Matrix.*/
    virtual void setByMatrix(const osg::Matrix& matrix)
    {
        if (PyObject_HasAttrString(_self, "setByMatrix") ) {
            try {
                call_method<void>(_self, "setByMatrix", ptr(&matrix));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
    }

    /** set the position of the matrix manipulator using a 4x4 Matrix.*/
    virtual void setByInverseMatrix(const osg::Matrix& matrix) 
    {
        if (PyObject_HasAttrString(_self, "setByInverseMatrix") ) {
            try {
                call_method<void>(_self, "setByInverseMatrix", ptr(&matrix));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
    }

    /** get the position of the manipulator as 4x4 Matrix.*/
    virtual osg::Matrix getMatrix() const {
        if (PyObject_HasAttrString(_self, "getMatrix") ) {
            try {
                return call_method<osg::Matrix>(_self, "getMatrix");
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
        return osg::Matrix();
    }

        /** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
    virtual osg::Matrix getInverseMatrix() const {
        if (PyObject_HasAttrString(_self, "getInverseMatrix") ) {
            try {
                return call_method<osg::Matrix>(_self, "getInverseMatrix");
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
        return osg::Matrix();
    }

    /** Get the FusionDistanceMode. Used by SceneView for setting up setereo convergence.*/
    virtual osgUtil::SceneView::FusionDistanceMode getFusionDistanceMode() const 
    {
        return osgUtil::SceneView::PROPORTIONAL_TO_SCREEN_DISTANCE;
    }

    /** Get the FusionDistanceValue. Used by SceneView for setting up setereo convergence.*/
    virtual float getFusionDistanceValue() const
    {
        return 1.0f;
    }

    /**
    Attach a node to the manipulator, automatically detaching any previously attached node.
    setNode(NULL) detaches previous nodes.
    May be ignored by manipulators which do not require a reference model.
    */
    virtual void setNode(osg::Node* node)
    {
        if (PyObject_HasAttrString(_self, "setNode") ) {
            try {
                call_method<void>(_self, "setNode", ptr(node));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
    }
    
    /** Return const node if attached.*/
    virtual const osg::Node* getNode() const 
    {
        if (PyObject_HasAttrString(_self, "getNode") ) {
            try {
                call_method<osg::Node *>(_self, "getNode");
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
        return NULL;
    }

    /** Return node if attached.*/
    virtual osg::Node* getNode()
    {
        if (PyObject_HasAttrString(_self, "getNode") ) {
            try {
                call_method<osg::Node *>(_self, "getNode");
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
        return NULL;
    }

    /**
    Move the camera to the default position. 
    May be ignored by manipulators if home functionality is not appropriate.
    */
    virtual void home(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa)
    {
        if (PyObject_HasAttrString(_self, "home") ) {
            try {
                call_method<void>(_self, "home", ptr(&ea), ptr(&aa));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
    }
    /**
    start/restart the manipulator.
    fixme: what does this actually mean? provide examples.
    */
    virtual void init(const osgGA::GUIEventAdapter& ea , osgGA::GUIActionAdapter& aa)
    {
        if (PyObject_HasAttrString(_self, "init") ) {
            try {
                call_method<void>(_self, "init", ptr(&ea), ptr(&aa));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        }
    }

    /** Handle events, return true if handled, false otherwise. */
    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
    {
        if (PyObject_HasAttrString(_self, "handle") ) {
            try {
                return call_method<bool>(_self, "handle", ptr(&ea), ptr(&aa));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
                return false;
            }
        } else {
            return osgGA::CameraManipulator::handle(ea, aa);
        }
    }

#if 0
    // TODO ??
    /** Handle visitations */
    virtual void accept(osgGA::GUIEventHandlerVisitor& v)
    {
        v.visit(*this);
    }
#endif

  protected:
    PyObject * _self;
};
} // namespace

namespace PyOSG {
void init_MatrixManipulator()
{
    // class_<osgGA::CameraManipulator, CameraManipulator, bases<osgGA::GUIEventHandler>, boost::noncopyable>("MatrixManipulator_base")

    class_<osgGA::CameraManipulator, CameraManipulator, bases<osgGA::GUIEventHandler>, boost::noncopyable>("MatrixManipulator_base")
/**
CameraManipulator is an abstract base class defining the interface, and a certain
amount of default functionality, for classes which wish to control OSG cameras
in response to GUI events.
*/
        ;
}
} // namespace PyOSG
