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

// This file contains all the functors for osg::Drawable. Had to split
// it from Drawable.cpp since VC7 gave an ICE.

#include <boost/python/scope.hpp>
#include <boost/python/class.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/extract.hpp>

#include <iostream>
#include <osg/Drawable>
#include <osg/TriangleFunctor>
#include <osg/PrimitiveSet>

#include "held_ptr.hpp"
#include "Drawable.hpp"

using namespace boost::python;

namespace {

class vec3cont
{
  public:
    typedef osg::Vec3 * iterator;
    vec3cont() : _begin(0), _end(0) {}
    vec3cont(const vec3cont & cp) : _begin(cp._begin), _end(cp._end) {}
    vec3cont(osg::Vec3 * b, int e):_begin(b), _end(b + e) {}

    osg::Vec3 * begin() { return _begin; }
    osg::Vec3 * end() { return _end; }
  private:
    osg::Vec3 * _begin;
    osg::Vec3 * _end;
};


class AttributeFunctor : public osg::Drawable::AttributeFunctor
{
    public:
        AttributeFunctor(PyObject * p) : _self(p) {
             Py_XINCREF(_self);
        }
        ~AttributeFunctor()
        {
            Py_XDECREF(_self);
        }
        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLbyte*) {}
        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLshort*) {}
        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLint*) {}

        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLubyte*) {}
        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLushort*) {}
        virtual void apply(osg::Drawable::AttributeType,unsigned int,GLuint*) {}

        virtual void apply(osg::Drawable::AttributeType,unsigned int,float*) {}
        virtual void apply(osg::Drawable::AttributeType,unsigned int,osg::Vec2*) {}
        virtual void apply(osg::Drawable::AttributeType atype,unsigned int cnt,osg::Vec3 * begin)
        {
            try {
                vec3cont cont(begin, cnt);
                call_method<void>(_self, "apply", object(atype), object(cont));
                return;
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
                return;
            }
        }
        virtual void apply(osg::Drawable::AttributeType,unsigned int,osg::Vec4*) {}
//        virtual void apply(osg::Drawable::AttributeType,unsigned int,osg::UByte4*) {} // Not in OSG's cvs code jbw

    private:
        PyObject * _self;
};

struct TFApply
{
    void operator()(const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, bool) const
    {
        try {
            call_method<void>(functor, "apply", v1, v2, v3);
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
    }
    void setFunctor(PyObject * object) { functor = object; }
    PyObject * functor;
};

typedef osg::TriangleFunctor<TFApply> TFunctor;

class VertexFunctor : public osg::PrimitiveFunctor
{
    public:
     VertexFunctor() {}
     virtual ~VertexFunctor() {}

     virtual void setVertexArray(unsigned int count,const osg::Vec2* vertices) {}
     virtual void setVertexArray(unsigned int count,const osg::Vec3* vertices) {}
     virtual void setVertexArray(unsigned int count,const osg::Vec4* vertices) {}
     
     virtual void drawArrays(GLenum mode,GLint first,GLsizei count) {}
     virtual void drawElements(GLenum mode,GLsizei count,const GLubyte* indices) {}
     virtual void drawElements(GLenum mode,GLsizei count,const GLushort* indices) {}
     virtual void drawElements(GLenum mode,GLsizei count,const GLuint* indices) {}
     
     virtual void begin(GLenum mode) {}
     virtual void vertex(const osg::Vec2& vert) {}
     virtual void vertex(const osg::Vec3& vert) {}
     virtual void vertex(const osg::Vec4& vert) {}
     virtual void vertex(float x,float y) {}
     virtual void vertex(float x,float y,float z) {}
     virtual void vertex(float x,float y,float z, float w) {}
     virtual void end() {}
};

// TODO check for all functors
void osgDrawable_accept(osg::Drawable * self, PyObject * functor)
{
    if (extract<TFunctor*>(functor).check()) {
        TFunctor tf;
        tf.setFunctor(functor);
        self->accept(tf);
    } else if (extract<AttributeFunctor *>(functor).check()) {
        // std::cerr << "osgDrawable_accept, received AttributeFunctor\n";
        AttributeFunctor * af = extract<AttributeFunctor *>(functor);
        self->accept(*af);
    } else {
        std::cerr << "osgDrawable_accept, functor is not a known functor\n";
        PyErr_Clear();
        return;
    }

}

} // namespace

namespace PyOSG {

extern class_Drawable * DrawableClass;

void init_Drawable3()
{
    class_<TFunctor, boost::noncopyable>("TriangleFunctor", no_init)
        .def(init<>())
        ;

    // FIXME
#if 0
    class_<VertexFunctor, boost::noncopyable>("VertexFunctor", no_init)
        .def(init<>())
        ;
#endif

    scope drawable_class(*DrawableClass);

    (*DrawableClass)
         .def("accept", &osgDrawable_accept)
    ;

    class_<osg::Drawable::AttributeFunctor, AttributeFunctor, boost::noncopyable>("AttributeFunctor", no_init)
        .def(init<>())
        ;

    // Internal classes, for iterator support in Functors
    class_<vec3cont>("vec3container")
        .def(init<osg::Vec3 *, int>())
        .def(init<vec3cont &>())
        .def("__iter__", range<return_value_policy<reference_existing_object> >(&vec3cont::begin, &vec3cont::end))
        ;

}
} // namespace PyOSG

