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

#include <boost/python/class.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/call.hpp>
#include <boost/python/object.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/extract.hpp>
#include <boost/ref.hpp>

#include <osg/Drawable>

#include <string>
#include <iostream>

#include "held_ptr.hpp"
#include "Math.hpp"

using namespace boost::python;

namespace PyOSG {

class DrawableBase : public osg::Drawable {
  public:
    DrawableBase() : osg::Drawable() {}
    ~DrawableBase() {}
    DrawableBase(const DrawableBase& geometry,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY) {}

    virtual osg::Object* cloneType() const { return NULL; }
    virtual osg::Object* clone(const osg::CopyOp& copyop) const { return NULL; }
    virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const Drawable*>(obj)!=NULL; }
    virtual const char* libraryName() const { return "osg"; }
    virtual const char* className() const { return "Drawable"; }

    virtual void drawImplementation(osg::State & state) const {}
    // FIXME
//    virtual osg::BoundingBox computeBound() const { return osg::BoundingBox();}
};

class Drawable_imp : public DrawableBase {
  public :
    Drawable_imp(PyObject * p) : DrawableBase(), _self(p) { Py_XINCREF(_self); }
    ~Drawable_imp() {}

    virtual void drawImplementation(osg::State & state) const {
        try {
            call_method<void>(_self, "drawImplementation", ptr(&state));
            return;
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
            return;
        }
    }

    // FIXME
#if 0
    virtual osg::BoundingBox computeBound() const {
        if (PyObject_HasAttrString(_self, "computeBound") ) {
            try {
                return call_method<osg::BoundingBox>(_self, "computeBound");
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
                return osg::BoundingBox();
            }
        } else {
            return osg::Drawable::computeBound();
        }
        // Code not reached
        // return osg::BoundingBox();
    }
#endif

  private :
    PyObject * _self;
};

void init_Drawable2()
{
    class_<DrawableBase, osg::ref_ptr<Drawable_imp>, bases<osg::Drawable>, boost::noncopyable > ("Drawable_base", no_init)
        ;
}
} // namespace PyOSG
