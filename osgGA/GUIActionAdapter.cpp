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

#include <osgGA/GUIActionAdapter>

using namespace boost::python;

namespace {
class GUIActionAdapterBase : public osgGA::GUIActionAdapter {
  public:
    GUIActionAdapterBase() {}
    virtual void requestRedraw() {}
    virtual void requestContinuousUpdate(bool needed=true) {}
    virtual void requestWarpPointer(float x,float y) {}
};

class GUIActionAdapterBase_imp : public GUIActionAdapterBase {
  public:
    GUIActionAdapterBase_imp(PyObject * p) : _self(p) {
        Py_XINCREF(_self);
    }
    virtual ~GUIActionAdapterBase_imp() {
        Py_XDECREF(_self);
    }

    virtual void requestRedraw() {
        try {
            call_method<void>(_self, "requestRedraw");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return;
    }

    virtual void requestContinuousUpdate(bool needed=true) {
        try {
            call_method<void>(_self, "requestContinuousUpdate", needed);
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return;
    }
    virtual void requestWarpPointer(float x,float y) {
        try {
            call_method<void>(_self, "requestWarpPointer", x, y);
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return;
    }
  private:
    PyObject * _self;
};

} // namespace

namespace PyOSG {
void init_GUIActionAdapter()
{
    class_<osgGA::GUIActionAdapter, boost::noncopyable>("GUIActionAdapter", no_init)
        .def("requestRedraw", 
            &osgGA::GUIActionAdapter::requestRedraw)
        .def("requestContinuousUpdate", 
            &osgGA::GUIActionAdapter::requestContinuousUpdate)
        .def("requestWarpPointer", 
            &osgGA::GUIActionAdapter::requestWarpPointer)
        ;

    class_<GUIActionAdapterBase, GUIActionAdapterBase_imp, bases<osgGA::GUIActionAdapter>, boost::noncopyable> aa_base("GUIActionAdapter_base",
        "Abstract base class defining the interface by which GUIEventHandlers may request\n"
        "actions of the GUI system in use. These requests for actions should then be honoured\n"
        "by the GUI toolkit of the user's application.\n"
        "\n"
        "To provide more detail, when a GUIEventHandler (e.g. a TrackballManipulator)\n"
        "handles an incoming event, such as a mouse event, it may wish to make\n"
        "a request of the GUI. E.g. if a model is 'thrown', the trackball manipulator\n"
        "may wish to start a timer, and be repeatedly called, to continuously refresh the\n"
        "camera's position and orientation. However, it has no way of doing this, as it\n"
        "knows nothing of the window system in which it's operating. Instead, the\n"
        "GUIEventHandler issues it's request via a GUIActionAdapter, and the viewer\n"
        "in use should honour the request, using the GUI system in play.\n"
        "\n"
        "There is more than one way of using the GUIActionAdapter. E.g. it may be inherited\n"
        "into a Viewer class, as is done with osgGLUT::Viewer. Alternatively, a simple \n"
        "subclass of GUIActionAdapter (e.g. osgQt::QtActionAdapter) may be passed to\n"
        "the GUIEventHandler::handle() function; once the function has returned, the viewer\n"
        "will then unpack the results and work out what to do to respond to the\n"
        "requests.\n"
        "\n"
        "Also there are several ways to run your app and handle the updating of\n"
        "the window.  osgGLUT::Viewer always has a idle callback registered which does a\n"
        "redraw all the time.  osgGLUT::Viewer can safely ignore both requestRedraw() and\n"
        "requestContinousUpdate() as these are happening all the time anyway.\n"
        "\n"
        "Other apps will probably want to respond to the requestRedraw() and\n"
        "requestContinousUpdate(bool) and again there is more than one way to handle it.\n"
        "You can override requestRedraw() and implement to call your own window\n"
        "redraw straight away. Or you can implement so that a flag is set and\n"
        "then you then respond the flag being set in your own leisure.\n",
        no_init);
    aa_base
        .def(init<>())
        ;
}
}
