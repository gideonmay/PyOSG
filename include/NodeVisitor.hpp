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

#include <osg/NodeVisitor>

#include <boost/python/return_internal_reference.hpp>
#include <boost/python/class.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/ptr.hpp>
#include "held_ptr.hpp"

#if defined(_WIN32)
#   if defined(PY_OSG)
#      define PY_OSG_DECL __declspec(dllexport)
#   else
#      define PY_OSG_DECL __declspec(dllimport)
#   endif
#else
#   define PY_OSG_DECL
#endif

namespace PyOSG {
using namespace boost::python;

typedef osg::NodeVisitor NodeVisitor;

class MyNodeVisitor : public osg::NodeVisitor
{
    public:
        MyNodeVisitor(PyObject * p) : _self(p) { Py_XINCREF(_self); }
        MyNodeVisitor(PyObject * p,osg::NodeVisitor::TraversalMode mode) : osg::NodeVisitor(mode), _self(p){ }
        MyNodeVisitor(PyObject * p, osg::NodeVisitor::VisitorType type,osg::NodeVisitor::TraversalMode mode) : osg::NodeVisitor(type, mode), _self(p){ }
        ~MyNodeVisitor() { }

        virtual void apply(osg::Node& node) {
            try {
                boost::python::call_method<void>(_self, "apply", boost::python::ptr(&node));
            } catch(...) {
                throw_error_already_set();
            }
        }
        void traverse_imp(osg::Node* node)
        {
            this->NodeVisitor::traverse(*node);
        }

    private:
        PyObject * _self;
};


typedef class_<osg::NodeVisitor, osg::ref_ptr<MyNodeVisitor>, bases<osg::Referenced>, boost::noncopyable> class_NodeVisitor;

PY_OSG_DECL extern class_NodeVisitor * NodeVisitorClass;

template <class F> void register_castNodeVisitor(const char * name, F f)
{
    if (NodeVisitorClass) {
        NodeVisitorClass->def(name, &f, boost::python::return_internal_reference<>());
    }
}
}

