#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/detail/api_placeholder.hpp>
#include <boost/python/errors.hpp>

#include <sstream>
#include <string>
#include <iostream>

#include <osg/Array>

#include "held_ptr.hpp"
#include "Math.hpp"

using namespace boost::python;

template <typename T, typename BT>
class TemplateIndexArray
{
  public :
    TemplateIndexArray(const char * name) : _array(name, boost::python::no_init) {
        _array
            .def(init<>())
            .def(init<unsigned int>())
            .def("__init__", make_constructor(&create_from_tuple))
            .def("getNumElements", &T::getNumElements)
            .def("__getitem__", &getitem)
            .def("__setitem__", &setitem)
            .def("resize", &resize)
            .def("__str__", &str)
            .def("__repr__", &repr)
            .def("set", &set)
            .def("reserve", &T::reserve)
            .def("index", &T::index)
            .def("push_back", &T::push_back)
            .def("size", &T::size)
            .def("max_size", &T::max_size)
            .def("capacity", &T::capacity)
            .def("empty", &T::empty)
            .def("__len__", &T::size)
            .def("__iter__", iterator<T>())
             ;
    }

    template <class F>
    void def(char const * name, F f)
    {
        _array.def(name, f);
    }

    static BT getitem(T * self, int idx) { 
        if (self->size() <= (unsigned int) idx) {
            PyErr_SetString(PyExc_IndexError, "assignment index out of range");
            throw_error_already_set();
        }
        return (*self)[idx]; 
    }

    static void setitem(T * self, int idx, BT val) { 
        if (self->size() <= (unsigned int) idx) {
            PyErr_SetString(PyExc_IndexError, "list index out of range");
            throw_error_already_set();
        } else {
            (*self)[idx] = val; 
        }
    }

    static std::string str(T * self)
    {
        std::ostringstream ost;
        ost << "(";
        for (unsigned int i =0 ; i<self->size() ; i++) {
            ost << int((*self)[i]);
            if (i != self->size() -1) ost << ",";
        }
        ost << ")";
        return ost.str();
    }

    static std::string repr(T * self)
    {
        std::ostringstream ost;
        ost << self->className() << "(";
        for (unsigned int i =0 ; i<self->size() ; i++) {
            ost << int((*self)[i]);
            if (i != self->size() -1) ost << ",";
        }
        ost << ")";
        return ost.str();
    }

    static void set(T * self, tuple elems)
    {
        self->clear();

        int elcount = len(elems);
        if (elcount == 0) return;

        self->resize(elcount);
        for (int i=0; i<elcount ; i++) {
            (*self)[i] = extract<BT>(elems[i]);
        }
    }

    static void resize(T * self, int size) { self->resize(size); }

    static osg::ref_ptr<T> create_from_tuple(tuple elems)
    {
        osg::ref_ptr<T> self(new T);
        set(self.get(), elems);
        return self;
    }


  private:
    class_<T, osg::ref_ptr<T>, bases<osg::IndexArray>, boost::noncopyable> _array;
};
