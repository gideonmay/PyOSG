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

#include <boost/python.hpp>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>

#include <osg/Matrix>
#include <osg/Quat>
#include <osg/Vec3>


#include "held_ptr.hpp"
#include "Math.hpp"


using namespace boost::python;

namespace {
std::string Matrix_str(osg::Matrix * self)
{
    std::ostringstream ost;
    ost << "(";
    for (unsigned int i=0 ; i<4; i++) {
        ost << "  (" << (*self)(i,0) << "," << (*self)(i,1) << "," << (*self)(i,2) << "," << (*self)(i,3) << ")";
        if (i != 3) ost << ",";
    }
    ost << ")";
    return ost.str();
}

void Matrix_setitem(osg::Matrix * self, int idx, float val)
{
    if (idx < 0 || idx >= 16) {
        PyErr_SetString(PyExc_IndexError, "range[0,15]");
        throw_error_already_set();
        return;
    }
    (*self)(idx /4, idx % 4) = val;
}

double Matrix_getitem(osg::Matrix * self, int idx)
{
    if (idx < 0 || idx >= 16) {
        PyErr_SetString(PyExc_IndexError, "range[0,15]");
        throw_error_already_set();
        return 0.0;
    }
    return (*self)(idx /4, idx % 4);
}

void Matrix_set(osg::Matrix * self, tuple matarray)
{
    size_t elements = len(matarray);

    if (elements != 16) {
        PyErr_SetString(PyExc_ValueError, "bad tuple length, should be 16");
        throw_error_already_set();
        return;
    }

    for (size_t i=0; i<elements ; i++) {
        float val = extract<float>(matarray[i]);
        (*self)(i / 4, i % 4) = val;
    }
}
float Matrix_get(osg::Matrix * self, int row, int col)
{
    if (row < 0 || row >= 4 || col < 0 || col >= 4) {
        PyErr_SetString(PyExc_IndexError, "row, col should be between 0..3");
        throw_error_already_set();
        return 0;
    }
    return (*self)(row, col);
}

osg::Matrix * Matrix_from_tuple(tuple matarray)
{
    osg::Matrix*  self = new osg::Matrix;

    Matrix_set(self, matarray);
    return self;
}


#ifdef OSG_USE_FLOAT_MATRIX
float *
#else
double *
#endif
Matrix_call(osg::Matrix * self, int row, int col)
{
    if (row < 0 || row >= 4 || col < 0 || col >= 4) {
        PyErr_SetString(PyExc_IndexError, "row, col should be between 0..3");
        throw_error_already_set();
        return 0;
    }
    return self->ptr() + row * 4 + col;
}

#ifdef OSG_USE_FLOAT_MATRIX
osg::Matrixf::value_type * asRaw(osg::Matrixf& self)
#else
osg::Matrixd::value_type * asRaw(osg::Matrixd& self)
#endif
{
    return self.ptr();
}

list asList(osg::Matrix * self)
{
    list l;

    for (int i = 0; i<4; i++) {
        for (int j=0 ; j<4; j++) {
            l.append((*self)(i,j));
        }
    }
    return l;
}

std::string RefMatrix_str(osg::RefMatrix * self)
{
    std::ostringstream ost;
    ost << "(";
    for (unsigned int i=0 ; i<4; i++) {
        ost << "  (" << (*self)(i,0) << "," << (*self)(i,1) << "," << (*self)(i,2) << "," << (*self)(i,3) << ")";
        if (i != 3) ost << ",";
    }
    ost << ")";
    return ost.str();
}

std::string RefMatrix_repr(osg::RefMatrix * self)
{
    std::ostringstream ost;
    ost << self->className() << "((";
    for (unsigned int i =0 ; i<4 ; i++) {
        ost << "(";
        for (unsigned int  j=0; j < 4 ; j++) {
            ost << (*self)(i,j);
            if (j != 3) ost << ",";
        }
        ost << ")";
        if (i != 3) ost << ",";
    }
    ost << "))";
    return ost.str();
}

osg::RefMatrix* RefMatrix_from_tuple(tuple matarray)
{
    osg::RefMatrix* self = new osg::RefMatrix;
    Matrix_set(self, matarray);
    return self;
}

} // namespace

namespace PyOSG {

void init_matrix2(class_<osg::Matrix> &matrix);

using namespace osg;

void init_matrix()
{
    class_<osg::Matrix> matrix("Matrix");
    matrix
        .def(init<const osg::Matrixd&>())
        .def(init<const osg::Matrixf&>())
        .def(init<const osg::Quat&>())
        .def("__init__", make_constructor(Matrix_from_tuple))
        .def("compare", &osg::Matrix::compare)
        .def("valid", &osg::Matrix::valid)
        .def("isNaN", &osg::Matrix::isNaN)
#ifdef OSG_USE_DOUBLE_MATRICES
        .def("set", (void (osg::Matrixd::*)(const osg::Matrixd&)) &osg::Matrixd::set)
#else
        .def("set", (void (osg::Matrixf::*)(const osg::Matrixf&)) &osg::Matrixf::set)
#endif
        .def("set", &Matrix_set) // Set the matrix, given a tuple with 16 floats
        .def("get", &Matrix_get)
        .def("get", &osg::Matrix::get)
    //     .def("__call__", &Matrix_call, return_value_policy<reference_existing_object>())
        .def("__call__", &Matrix_get)
        .def("__setitem__", &Matrix_setitem)
        .def("__getitem__", &Matrix_getitem)

    // Disabled, since there are too many parameters for the default BOOST_PYTHON_MAX_ARITY
    // .def("set", (void (Matrix::*)(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float)) &Matrix::set)

        .def("makeIdentity", &Matrix::makeIdentity)

        .def("makeScale", (void (Matrix::*)(const Vec3&))&Matrix::makeScale)
        .def("makeScale", (void (Matrix::*)(Matrix::value_type, Matrix::value_type, Matrix::value_type))&Matrix::makeScale)

        .def("makeTranslate", (void (Matrix::*)(const Vec3&))&Matrix::makeTranslate)
        .def("makeTranslate", (void (Matrix::*)(Matrix::value_type, Matrix::value_type, Matrix::value_type))&Matrix::makeTranslate)

        .def("makeRotate", (void (Matrix::*)(const Vec3&, const Vec3&))&Matrix::makeRotate)
        .def("makeRotate", (void (Matrix::*)(Matrix::value_type, const Vec3&))&Matrix::makeRotate)
        .def("makeRotate", (void (Matrix::*)(Matrix::value_type, Matrix::value_type, Matrix::value_type, Matrix::value_type))&Matrix::makeRotate)
        .def("makeRotate", (void (Matrix::*)(const Quat&))&Matrix::makeRotate)
        .def("makeRotate", (void (Matrix::*)(Matrix::value_type, const Vec3&, Matrix::value_type, const Vec3&, Matrix::value_type, const Vec3&))
                 &Matrix::makeRotate)

        .def("makeOrtho", &Matrix::makeOrtho)
        /** Set to a orthographic projection. See glOrtho for further details.*/
        .def("makeOrtho2D", &Matrix::makeOrtho2D)
        /** Set to a 2D orthographic projection. See glOrtho2D for further details.*/

        .def("makeFrustum", &Matrix::makeFrustum)
        /** Set to a perspective projection. See glFrustum for further details.*/

        .def("makePerspective", &Matrix::makePerspective)
        /** Set to a symmetrical perspective projection, See gluPerspective for further details.
          * Aspect ratio is defined as width/height.*/

        .def("makeLookAt", &Matrix::makeLookAt)
        /** Set to the position and orientation as per a camera, using the same convention as gluLookAt. */

        .def("invert", &Matrix::invert)

        .def("preMult", (void (Matrix::*)(const Matrix&)) &Matrix::preMult)
        .def("postMult", (void (Matrix::*)(const Matrix&)) &Matrix::postMult)
        .def("preMult", (Vec3 (Matrix::*)(const Vec3&) const) &Matrix::preMult)
        .def("postMult", (Vec3 (Matrix::*)(const Vec3&) const) &Matrix::postMult)
        .def("preMult", (Vec4 (Matrix::*)(const Vec4&) const) &Matrix::preMult)
        .def("postMult", (Vec4 (Matrix::*)(const Vec4&) const) &Matrix::postMult)

        .def(self * self)
         // .def(self *= self)
         //
        .def("getRotate", &Matrix::getRotate)
        .def("setTrans", (void (Matrix::*)(Matrix::value_type, Matrix::value_type, Matrix::value_type)) &Matrix::setTrans)
        .def("setTrans", (void (Matrix::*)(const Vec3&)) &Matrix::setTrans)
        .def("getTrans", &Matrix::getTrans)
        .def("getScale", &Matrix::getScale)

        .def("mult", &Matrix::mult)


        .def("asRaw", &asRaw, return_value_policy<return_opaque_pointer>())
        // .def("asFloats", &asFloats, return_value_policy<return_opaque_pointer>())

        .def("asList", &asList)

        .def(Vec3() * self)
        .def(Vec4() * self)

        .def("__str__", &Matrix_str)

         ;
    // Ugly workaround another MSV7 ICE - C1204 internal structure overflow
    init_matrix2(matrix);

    class_<RefMatrix, ref_ptr<RefMatrix>, bases<Matrix, Object> > ref_matrix("RefMatrix", no_init);
    ref_matrix
        .def(init<>())
        // .def("__init__", make_constructor(RefMatrix_from_tuple))
        // .def(init<const RefMatrix &> ())

        .def("cloneType",
            &RefMatrix::cloneType, 
            return_value_policy<manage_osg_object>())

        .def("clone",
            &RefMatrix::clone,
            return_value_policy<manage_osg_object>())
        .def("__str__", &RefMatrix_str)
        .def("__repr__", &RefMatrix_repr)
        ;
}
}
