// Copyright (C) 2002-2003 Gideon May (gideon@computer.org)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

#ifndef PYOSG_HELD_PTR
#define PYOSG_HELD_PTR 1

#include <boost/python/detail/indirect_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/python/to_python_indirect.hpp>
#include <boost/type_traits/composite_traits.hpp>

#include <boost/python/to_python_converter.hpp>
#include <boost/python/implicit.hpp>

#if 0
#include <Producer/Referenced>
#endif

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Node>

#define TEST_REF 1

#if 0
namespace boost { namespace python {

template<class T> inline T * get_pointer(osg::ref_ptr<T> const & p)
{
    return const_cast<T *>(p.get());
}

#if 0
template<class T> inline T * get_pointer(Producer::ref_ptr<T> const & p)
{
    return const_cast<T *>(p.get());
}
#endif

}} // namespace boost:python
#endif

struct make_osg_holder
{
  template <class T>
  static PyObject* execute(T* p)
  {
      typedef osg::ref_ptr<T> smart_pointer;
      typedef boost::python::objects::pointer_holder<smart_pointer, T> holder_t;

      smart_pointer ptr(p);
      return boost::python::objects::make_ptr_instance<T, holder_t>::execute(ptr);
  }
};

template <class R>
struct manage_osg_object_requires_a_pointer_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
{}
# endif
;

template <class R>
struct manage_osg_object_requires_a_pointer_or_reference_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
  {}
# endif
;

struct manage_osg_object
{
    template <class T>
    struct apply
    {
#if TEST_REF
        BOOST_STATIC_CONSTANT(
            bool, ok = boost::is_pointer<T>::value || boost::is_reference<T>::value);
        typedef typename boost::mpl::if_c<
            ok
            , boost::python::to_python_indirect<T, make_osg_holder>
            , manage_osg_object_requires_a_pointer_or_reference_return_type<T>
        >::type type;
#else
        typedef typename boost::mpl::if_c<
            boost::is_pointer<T>::value
            , boost::python::to_python_indirect<T, make_osg_holder>
            , manage_osg_object_requires_a_pointer_return_type<T>
        >::type type;
#endif
    };
};

#if 0
struct make_producer_holder
{
  typedef PyObject* result_type;
  template <class T>
  static result_type execute(T* p)
  {
      typedef Producer::ref_ptr<T> smart_pointer;
      typedef boost::python::objects::pointer_holder<smart_pointer, T> holder_t;

      smart_pointer ptr(p);
      return boost::python::objects::make_ptr_instance<T, holder_t>::execute(ptr);
  }
};

template <class R>
struct manage_producer_object_requires_a_pointer_return_type
# if defined(__GNUC__) && __GNUC__ >= 3 || defined(__EDG__)
{}
# endif
;

struct manage_producer_object
{
    template <class T>
    struct apply
    {
        typedef typename boost::mpl::if_c<
            boost::is_pointer<T>::value
            , boost::python::to_python_indirect<T, make_producer_holder>
            , manage_producer_object_requires_a_pointer_return_type<T>
        >::type type;
    };
};
#endif

template <class T>
struct enum_to_int_converter
{
   static PyObject* convert(T const& x)
   {
          return PyInt_FromLong(x);
   }
};

template <class T> 
void enum_as_int()
{
        boost::python::to_python_converter<T, enum_to_int_converter<T> >();
        boost::python::implicitly_convertible<int, T>();
};

#endif // PYOSG_HELD_PTR
