#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/detail/api_placeholder.hpp>
#include <boost/python/errors.hpp>

#include <string>
#include <iostream>
#include <sstream>

#include <osg/Array>

#include "held_ptr.hpp"
#include "Math.hpp"

using namespace boost::python;

template <typename T, typename BT>
class TemplateCompArray
{
  public :
    TemplateCompArray(const char * name) : _array(name, boost::python::no_init) {
        _array
            .def(init<>())
            .def(init<int>())
            .def("__init__", make_constructor(&create_from_tuple))
            .def("getNumElements", &T::getNumElements)
            .def("__getitem__", &getitem, return_internal_reference<>())
            .def("__setitem__", &setitem, return_internal_reference<>())
            .def("resize", &resize)
            .def("__str__", &str)
            .def("__repr__", &repr)
            .def("set", &set)
            .def("reserve", &T::reserve)
            .def("push_back", &T::push_back)
            .def("size", &T::size)
            .def("max_size", &T::max_size)
            .def("capacity", &T::capacity)
            .def("empty", &T::empty)
            .def("__len__", &T::size)
            .def("__iter__", iterator<T, boost::python::return_internal_reference<> >())
             ;
    }

    template <class F>
    void def(char const * name, F f)
    {
        _array.def(name, f);
    }

    static BT& getitem(T * self, int idx) { 
        if (self->size() <= (unsigned int) idx) {
            PyErr_SetString(PyExc_IndexError, "assignment index out of range");
            throw_error_already_set();
        }
        return (*self)[idx]; 
    }

    static void setitem(T * self, int idx, const BT& val) { 
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
            ost << "(";
            for (int j=0; j < self->getDataSize() ; j++) {
                ost << (*self)[i][j];
                if (j != self->getDataSize() - 1) ost << ",";
            }
            ost << ")";
            if (i != self->size() -1) ost << ",";
        }
        ost << ")";
        return ost.str();
    }

    static std::string repr(T * self)
    {
        std::ostringstream ost;
        ost << self->className() << "((";
        for (unsigned int i =0 ; i<self->size() ; i++) {
            ost << "(";
            for (int  j=0; j < self->getDataSize() ; j++) {
                ost << (*self)[i][j];
                if (j != self->getDataSize() - 1) ost << ",";
            }
            ost << ")";
            ost << ",";
        }
        ost << "))";
        return ost.str();
    }

    static void set(T * self, tuple elems)
    {
        self->clear();

        int elcount = len(elems);
        if (elcount == 0) return;

        self->resize(elcount);

        const object& el = elems[0];
        if (PyOSG::check_tuple(el) && len(el) == self->getDataSize()) {
            for (int i=0; i<elcount ; i++) {
                extract<tuple> vertex(elems[i]);
                for (int j=0 ; j<self->getDataSize(); j++) {
                    (*self)[i][j] =extract<float>(vertex()[j]);
                }
            }
        } else {
            PyErr_SetString(PyExc_ValueError, "Bad element size");
            throw_error_already_set();
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
    class_<T, osg::ref_ptr<T>, bases<osg::Array>, boost::noncopyable> _array;
};

