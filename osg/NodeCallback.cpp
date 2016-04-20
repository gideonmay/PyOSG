// TODO nestedCallback

#include <boost/python/class.hpp>
#include <boost/python/call_method.hpp>

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
