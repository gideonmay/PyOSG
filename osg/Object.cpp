#include <boost/python.hpp>

#include <string>
#include <iostream>

#include <osg/Object>
#include "held_ptr.hpp"

using namespace boost::python;

namespace {

// Reference http://www.boost.org/libs/python/doc/tutorial/doc/class_virtual_functions.html

// free caller functions

/** Clone the type of an object, with Object* return type. Must be defined by derived classes.*/
osg::Object* call_cloneType(osg::Object& obj) { return obj.cloneType(); }

/** Clone the an object, with Object* return type. Must be defined by derived classes.*/
osg::Object* call_clone(osg::Object& obj, const osg::CopyOp& copyop) { return obj.clone(copyop); }

//////////////////////////////////////////

class ObjectBase : public osg::Object {
  public:
      ObjectBase() : osg::Object() {}
};

class ObjectBase_imp : public ObjectBase {
  public:
    ObjectBase_imp(PyObject* self_)
            : self(self_)
    {
        Py_XINCREF(self);

    }

    ~ObjectBase_imp()
    {
        Py_XDECREF(self);
    }

    osg::Object* cloneType() const { return call_method<osg::Object*>(self, "cloneType"); }
    osg::Object* clone(const osg::CopyOp& copyop) const { return call_method<osg::Object*>(self, "clone", copyop); }

    bool isSameKindAs(const Object* obj) const { return osg::Object::isSameKindAs(obj); }

    // forced implementation
    const char* libraryName() const { return "osg"; }
    const char* className() const { return "Object"; }
  private:

    PyObject* self;
};

} //namespace

namespace PyOSG {
void init_Object()
{
    class_<osg::Object, osg::ref_ptr<osg::Object>, bases<osg::Referenced>, boost::noncopyable> obj("Object", no_init);

    scope object_scope(obj);
    obj
        .def("cloneType",
            &osg::Object::cloneType,
            return_value_policy<manage_osg_object>())

        .def("clone",
            &osg::Object::clone,
            return_value_policy<manage_osg_object>())

        .def("libraryName", 
            &osg::Object::libraryName)
        .def("className", 
            &osg::Object::className)
        .def("isSameKindAs", 
            &osg::Object::isSameKindAs)
        .def("setDataVariance", 
            &osg::Object::setDataVariance,
            "Set the data variance of this object.\n"
            "Can be set to either STATIC for values that do not change over the lifetime of the object,\n"
            "or DYNAMIC for values that vary over the lifetime of the object. The DataVariance value\n"
            "can be used be routines such as optimzation codes that wish to share static data.\n")
        .def("getDataVariance", 
            &osg::Object::getDataVariance,
            "Get the data variance of this object.")
        // .def("setUserData", &osg::Object::setUserData)
        //.def("getUserData", (osg::Referenced* (osg::Object::*)())
        //    &osg::Object::getUserData, return_internal_reference<>())
        ;
    {
        class_<ObjectBase, osg::ref_ptr<ObjectBase_imp>, bases<osg::Object>, boost::noncopyable> obj("Object_base", no_init);
        obj
            .def(init<>())
            ;
    }
#   define OSG_ENUM_VARIANCE(VALUE) variance.value(#VALUE, osg::Object::VALUE)
    enum_<osg::Object::DataVariance> variance("DataVariance");
    OSG_ENUM_VARIANCE(DYNAMIC);
    OSG_ENUM_VARIANCE(STATIC);
    variance.export_values();
}
}

