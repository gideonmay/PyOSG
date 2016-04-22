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

// TODO nestedCallback

#include <boost/python.hpp>

#include <osg/NodeCallback>
#include <osg/NodeVisitor>

#include "held_ptr.hpp"
#include "lock.hpp"

using namespace boost::python;

namespace PyOSG {
class PyNodeCallback : public osg::NodeCallback
{
  public:
    PyNodeCallback(PyObject * p) : osg::NodeCallback(), _self(p) {}
    ~PyNodeCallback() {}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        // std::cerr << "PyNodeCallback::operator(), thread id = " << PyThread_get_thread_ident() << std::endl;
        PYOSG_LOCK_INTERPRETER();
        try {
            call_method<void>(_self, "apply", ptr(node), ptr(nv));
        } catch(...) {
            handle_exception();
            PyErr_Print();
        }
        PYOSG_RELEASE_INTERPRETER();
    }
    void traverse_imp(osg::Node* node,osg::NodeVisitor* nv)
    {
        this->osg::NodeCallback::traverse(node, nv);
    }
  private:
      PyObject * _self;
};

void init_NodeCallback()
{
    class_<osg::NodeCallback, osg::ref_ptr<PyNodeCallback>, bases<osg::Referenced>, boost::noncopyable>("NodeCallback", no_init)
        .def(init<>())
        .def("traverse", &PyNodeCallback::traverse_imp)
        ;
}
}
