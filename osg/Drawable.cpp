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

// TODO missing docs and functors (partially implemented)

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include <osg/Drawable>
#include <osg/NodeVisitor>
#include <osg/TriangleFunctor>

#include <string>
#include <iostream>
#include "Drawable.hpp"

#include "held_ptr.hpp"
#include "Math.hpp"

using namespace boost::python;

namespace {

// Reference http://www.boost.org/libs/python/doc/tutorial/doc/class_virtual_functions.html

// free caller functions

/** Clone the type of an object, with Object* return type. Must be defined by derived classes.*/
osg::Object* call_cloneType(osg::Object& obj) { return obj.cloneType(); }

/** Clone the an object, with Object* return type. Must be defined by derived classes.*/
osg::Object* call_clone(osg::Object& obj, const osg::CopyOp& copyop) { return obj.clone(copyop); }

void call_drawImplementation(osg::Drawable& obj, osg::RenderInfo& info) { obj.drawImplementation(info); }

class DrawableWrapper : public osg::Drawable {
  public:
    DrawableWrapper(PyObject* self_)
            : self(self_) {}
    
    osg::Object* cloneType() const { return call_method<osg::Object*>(self, "cloneType"); }
    
    osg::Object* clone(const osg::CopyOp& copyop) const { return call_method<osg::Object*>(self, "clone", copyop); }

    void drawImplementation(osg::State& state) const { return call_method<void>(self, "drawImplementation", state); }

    PyObject* self;
};
} // namespace

namespace PyOSG {

class UpdateCallback : public osg::Drawable::UpdateCallback
{
    public:
        UpdateCallback(PyObject * p) : _self(p) {
            // std::cerr << "UpdateCallback:ctor\n";
            Py_XINCREF(_self);
        }
        ~UpdateCallback()
        {
            Py_XDECREF(_self);
        }

    virtual void update(osg::NodeVisitor *visitor, osg::Drawable* drawable) 
    {
        // std::cerr << "UpdateCallback:update\n";
        try {
            call_method<void>(_self, "update", ptr(visitor), ptr(drawable));
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
    }

    virtual void update_imp(osg::NodeVisitor *visitor, osg::Drawable* drawable) 
    {
        // is a pure virtual function
        // this->osg::Drawable::UpdateCallback::update(node, nv);
    }
  private:
    PyObject * _self;
};

class CullCallback : public osg::Drawable::CullCallback
{
    public:
        CullCallback(PyObject * p) : _self(p) {
             Py_XINCREF(_self);
        }
        ~CullCallback()
        {
            Py_XDECREF(_self);
        }

    virtual bool cull(osg::NodeVisitor *visitor, osg::Drawable* drawable, osg::State * state) const
    {
        try {
            return (bool) call_method<int>(_self, "cull", ptr(visitor), ptr(drawable), ptr(state));
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
            return false;
        }
    }

    virtual void cull_imp(osg::NodeVisitor *visitor, osg::Drawable* drawable)
    {
        // is a pure virtual function
        // this->osg::Drawable::CullCallback::cull(node, nv);
    }
  private:
    PyObject * _self;
};

class DrawCallback : public osg::Drawable::DrawCallback
{
  public:
    DrawCallback(PyObject * p) : _self(p) {
        Py_XINCREF(_self);
    }
    ~DrawCallback() {
        Py_XDECREF(_self);
    }
    /** do customized draw code.*/
    virtual void drawImplementation(osg::State& state,const osg::Drawable* drawable) const 
    {
        try {
            call_method<void>(_self, "drawImplementation", ptr(&state), ptr(drawable));
            return;
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
            return;
        }
    }
    virtual void drawImplementation_imp(osg::RenderInfo& info, const osg::Drawable* drawable) const
    {
        // FIXME!
        this->osg::Drawable::DrawCallback::drawImplementation(info, drawable);
    }
  private:
    PyObject * _self;
};

tuple getParents(osg::Drawable& self)
{
    list plist;
    osg::Drawable::ParentList::const_iterator piter;

    // FIXME
#if 0
    for(piter = self.getParents().begin(); piter < self.getParents().end(); piter++) {
        plist.append(object(const_cast<osg::Node *>(* piter)));
    }
#endif
    return tuple(piter);

}

} // namespace

namespace PyOSG {

class_Drawable * DrawableClass = NULL;

void init_Drawable()
{
    DrawableClass = new class_Drawable("Drawable",
        "Pure virtual base class for drawable Geometry.  Contains no drawing primitives\n"
        "directly, these are provided by subclasses such as osg::Geometry. State attributes \n"
        "for a Drawable are maintained in StateSet which the Drawable maintains\n"
        "a referenced counted pointer to.  Both Drawable's and StateSet's can \n"
        "be shared for optimal memory usage and graphics performance.\n",
        no_init);

    scope drawable_class(*DrawableClass);

    (*DrawableClass)
        .def("cloneType", &call_cloneType, return_internal_reference<>())
        .def("clone", &call_clone, return_internal_reference<>())
        .def("getParents",
            &getParents,
            "Get the parent list of drawable.\n")

                // FIXME
#if 0
        .def("getParent", 
            (osg::Node *(osg::Drawable::*)(unsigned int))
            &osg::Drawable::getParent,
            return_value_policy<manage_osg_object>())
#endif

        .def("getNumParents",
            &osg::Drawable::getNumParents)

        .def("setStateSet",
            &osg::Drawable::setStateSet)

        .def("getStateSet", 
            (osg::StateSet * ( osg::Drawable::*)())
            &osg::Drawable::getStateSet,
            return_value_policy<manage_osg_object>())

        .def("getOrCreateStateSet",
            (osg::StateSet * ( osg::Drawable::*)())
            &osg::Drawable::getOrCreateStateSet,
            return_value_policy<manage_osg_object>())

        .def("dirtyBound", &osg::Drawable::dirtyBound)
        .def("getBound",
            &osg::Drawable::getBound,
            return_value_policy<copy_const_reference>())

        .def("setShape",
            &osg::Drawable::setShape)

        .def("getShape",
            (osg::Shape *(osg::Drawable::*)())
            &osg::Drawable::getShape,
            return_value_policy<manage_osg_object>())

        .def("setSupportsDisplayList",
            &osg::Drawable::setSupportsDisplayList)
        .def("getSupportsDisplayList",
            &osg::Drawable::getSupportsDisplayList)

        .def("setUseDisplayList",
            &osg::Drawable::setUseDisplayList)
        .def("getUseDisplayList",
            &osg::Drawable::getUseDisplayList)

        .def("setUseVertexBufferObjects", &osg::Drawable::setUseVertexBufferObjects)
        .def("getUseVertexBufferObjects", &osg::Drawable::getUseVertexBufferObjects)
        .def("dirtyDisplayList",
            &osg::Drawable::dirtyDisplayList)

        .def("draw", &osg::Drawable::draw)
        .def("compileGLObjects", &osg::Drawable::compileGLObjects)

        .def("setUpdateCallback", &osg::Drawable::setUpdateCallback)
        .def("setCullCallback", &osg::Drawable::setCullCallback)
        .def("setDrawCallback", &osg::Drawable::setDrawCallback)
        //      &osg::Drawable::getDrawCallback, return_internal_reference<>())
        .def("drawImplementation", &osg::Drawable::drawImplementation)
        .def("drawImplementation", &call_drawImplementation)

        .def("deleteDisplayList", &osg::Drawable::deleteDisplayList)
        .def("flushDeletedDisplayLists", &osg::Drawable::flushDeletedDisplayLists)

        // FIXME
#if 0
        .def("deleteVertexBufferObject", &osg::Drawable::deleteVertexBufferObject)
        .def("flushDeletedVertexBufferObjects", &osg::Drawable::flushDeletedVertexBufferObjects)

        .def("getExtensions", &osg::Drawable::getExtensions, return_internal_reference<>())
        .def("setExtensions", &osg::Drawable::setExtensions)
#endif
    ;

    class_<osg::Drawable::UpdateCallback, osg::ref_ptr<UpdateCallback>, bases<osg::Referenced>, boost::noncopyable>("UpdateCallback", no_init)
        .def(init<>()) // calls the derived init function
        .def("update", &UpdateCallback::update_imp)
        ;

    class_<osg::Drawable::CullCallback, osg::ref_ptr<CullCallback>, bases<osg::Referenced>, boost::noncopyable>("CullCallback", no_init)
        .def(init<>()) // calls the derived init function
        .def("cull", &CullCallback::cull_imp)
        ;

    class_<osg::Drawable::DrawCallback, osg::ref_ptr<DrawCallback>, bases<osg::Referenced>, boost::noncopyable>("DrawCallback", no_init)
        .def(init<>()) // calls the derived init function
        .def("drawImplementation", &DrawCallback::drawImplementation_imp)
        ;

    class_<osg::Drawable::AttributeFunctor> attrFunctor("AttributeFunctor");
    attrFunctor
        .def(init<>())
    //  .def("apply", &osg::Drawable::AttributeFunctor::apply)
    ;

    // FIXME !!!
#if 0
    class_<osg::Drawable::Extensions, osg::ref_ptr<osg::Drawable::Extensions>, bases<osg::Referenced>, boost::noncopyable> extensions("Extensions", no_init);
    extensions
        .def(init<unsigned int>())
        //.def("lowestCommonDenominator", &osg::Drawable::Extensions::lowestCommonDenominator)

        .def("setupGLExtenions", &osg::Drawable::Extensions::setupGLExtenions)
        .def("setVertexProgramSupported", &osg::Drawable::Extensions::setVertexProgramSupported)
        .def("isVertexProgramSupported", &osg::Drawable::Extensions::isVertexProgramSupported)
        .def("setSecondaryColorSupported", &osg::Drawable::Extensions::setSecondaryColorSupported)
        .def("isSecondaryColorSupported", &osg::Drawable::Extensions::isSecondaryColorSupported)
        .def("setFogCoordSupported", &osg::Drawable::Extensions::setFogCoordSupported)
        .def("isFogCoordSupported", &osg::Drawable::Extensions::isFogCoordSupported)
        .def("setMultiTexSupported", &osg::Drawable::Extensions::setMultiTexSupported)
        .def("isMultiTexSupported", &osg::Drawable::Extensions::isMultiTexSupported)
        .def("setOcclusionQuerySupported", &osg::Drawable::Extensions::setOcclusionQuerySupported)
        .def("isOcclusionQuerySupported", &osg::Drawable::Extensions::isOcclusionQuerySupported)
        .def("setARBOcclusionQuerySupported", &osg::Drawable::Extensions::setARBOcclusionQuerySupported)
        .def("isARBOcclusionQuerySupported", &osg::Drawable::Extensions::isARBOcclusionQuerySupported)
        .def("glSecondaryColor3ubv", &osg::Drawable::Extensions::glSecondaryColor3ubv)
        .def("glSecondaryColor3fv", &osg::Drawable::Extensions::glSecondaryColor3fv)
        .def("glFogCoordfv", &osg::Drawable::Extensions::glFogCoordfv)
        .def("glMultiTexCoord1f", &osg::Drawable::Extensions::glMultiTexCoord1f)
        .def("glMultiTexCoord2fv", &osg::Drawable::Extensions::glMultiTexCoord2fv)
        .def("glMultiTexCoord3fv", &osg::Drawable::Extensions::glMultiTexCoord3fv)
        .def("glMultiTexCoord4fv", &osg::Drawable::Extensions::glMultiTexCoord4fv)
        .def("glVertexAttrib1s", &osg::Drawable::Extensions::glVertexAttrib1s)
        .def("glVertexAttrib1f", &osg::Drawable::Extensions::glVertexAttrib1f)
        .def("glVertexAttrib2fv", &osg::Drawable::Extensions::glVertexAttrib2fv)
        .def("glVertexAttrib3fv", &osg::Drawable::Extensions::glVertexAttrib3fv)
        .def("glVertexAttrib4fv", &osg::Drawable::Extensions::glVertexAttrib4fv)
        .def("glVertexAttrib4ubv", &osg::Drawable::Extensions::glVertexAttrib4ubv)
        .def("glVertexAttrib4Nubv", &osg::Drawable::Extensions::glVertexAttrib4Nubv)
        .def("glGenBuffers", &osg::Drawable::Extensions::glGenBuffers)
        .def("glBindBuffer", &osg::Drawable::Extensions::glBindBuffer)
        // XXX .def("glBufferData", &osg::Drawable::Extensions::glBufferData)
        // XXX .def("glBufferSubData", &osg::Drawable::Extensions::glBufferSubData)
        .def("glDeleteBuffers", &osg::Drawable::Extensions::glDeleteBuffers)
        .def("glGenOcclusionQueries", &osg::Drawable::Extensions::glGenOcclusionQueries)
        .def("glDeleteOcclusionQueries", &osg::Drawable::Extensions::glDeleteOcclusionQueries)
        .def("glIsOcclusionQuery", &osg::Drawable::Extensions::glIsOcclusionQuery) //returns a GLboolean
        .def("glBeginOcclusionQuery", &osg::Drawable::Extensions::glBeginOcclusionQuery)
        .def("glEndOcclusionQuery", &osg::Drawable::Extensions::glEndOcclusionQuery)
        .def("glGetOcclusionQueryiv", &osg::Drawable::Extensions::glGetOcclusionQueryiv)
        .def("glGetOcclusionQueryuiv", &osg::Drawable::Extensions::glGetOcclusionQueryuiv)
        .def("glGetQueryiv", &osg::Drawable::Extensions::glGetQueryiv)
        .def("glGenQueries", &osg::Drawable::Extensions::glGenQueries)
        .def("glBeginQuery", &osg::Drawable::Extensions::glBeginQuery)
        .def("glEndQuery", &osg::Drawable::Extensions::glEndQuery)
        .def("glIsQuery", &osg::Drawable::Extensions::glIsQuery) // returns GLboolean
        .def("glGetQueryObjectiv", &osg::Drawable::Extensions::glGetQueryObjectiv)
        .def("glGetQueryObjectuiv", &osg::Drawable::Extensions::glGetQueryObjectuiv)
        ;
#endif

#   define OSG_ENUM_TYPE(VALUE) type.value(#VALUE, osg::Drawable::VALUE)
    enum_<osg::Drawable::AttributeTypes> type("AttributeTypes");
    OSG_ENUM_TYPE(VERTICES);
    OSG_ENUM_TYPE(WEIGHTS);
    OSG_ENUM_TYPE(NORMALS);
    OSG_ENUM_TYPE(COLORS);
    OSG_ENUM_TYPE(SECONDARY_COLORS);
    OSG_ENUM_TYPE(FOG_COORDS);
    OSG_ENUM_TYPE(ATTRIBUTE_6);
    OSG_ENUM_TYPE(ATTRIBUTE_7);
    OSG_ENUM_TYPE(TEXTURE_COORDS);
    OSG_ENUM_TYPE(TEXTURE_COORDS_0);
    OSG_ENUM_TYPE(TEXTURE_COORDS_1);
    OSG_ENUM_TYPE(TEXTURE_COORDS_2);
    OSG_ENUM_TYPE(TEXTURE_COORDS_3);
    OSG_ENUM_TYPE(TEXTURE_COORDS_4);
    OSG_ENUM_TYPE(TEXTURE_COORDS_5);
    OSG_ENUM_TYPE(TEXTURE_COORDS_6);
    OSG_ENUM_TYPE(TEXTURE_COORDS_7);
    type.export_values();
}
} // namespace PyOSG

