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

#include <osgGA/GUIEventHandler>

using namespace boost::python;

namespace {
class GUIEventHandler : public osgGA::GUIEventHandler {
  public:
//    GUIEventHandler() : _self(NULL), osgGA::GUIEventHandler() { ref(); }

    GUIEventHandler(PyObject * self) : osgGA::GUIEventHandler(), _self(self){
//        ref(); 
    }

    ~GUIEventHandler() {
//        unref(); 
    }

    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
    {
        if (PyObject_HasAttrString(_self, "handle") ) {
            try {
                return call_method<bool>(_self, "handle", ptr(&ea), ptr(&us));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
                return false;
            }
        } else {
            return osgGA::GUIEventHandler::handle(ea, us);
        }
    }

    bool handle_imp(osgGA::GUIEventAdapter * ea,osgGA::GUIActionAdapter * us)
    {
        return osgGA::GUIEventHandler::handle(*ea, *us);
    }

#if 0 // ???
    virtual void accept(osgGA::GUIEventHandlerVisitor& hv)
    {
        if (PyObject_HasAttrString(_self, "accept") ) {
            try {
                return call_method<void>(_self, "accept", ptr(&hv));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        } else {
            return osgGA::GUIEventHandler::accept(hv);
        }
    }

    void accept_imp(osgGA::GUIEventHandlerVisitor* hv)
    {
        return osgGA::GUIEventHandler::accept(*hv);
    }
#endif

  protected:
    PyObject * _self;
};
} // namespace

namespace PyOSG {
void init_GUIEventHandler()
{
    class_<osgGA::GUIEventHandler, GUIEventHandler,  boost::noncopyable>("GUIEventHandler", no_init)
        .def(init<>())
        .def("handle", 
            &GUIEventHandler::handle_imp)
        // .def("accept", 
        //     &GUIEventHandler::accept_imp)
        ;

    // This class wrapper exists just for the sake of having a class available for
    // the EventHandlerList iterator defined in osgProducer::Viewer
    // Don't know if it is useful, mainly because of proof of concept
    //
    // Not instansiatable from within python
    class_< osg::ref_ptr<osgGA::GUIEventHandler>, boost::noncopyable>("GUIEventHandler_ref", no_init)
        ;
}
}
