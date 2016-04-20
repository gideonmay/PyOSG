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

#include <boost/python/class.hpp>

#include <osg/Matrix>
#include <osg/Quat>
#include <osg/Vec3>

#include "Math.hpp"


using namespace boost::python;
using namespace osg;

namespace {
#ifdef WIN32
void preMult(osg::Matrix * self, const Matrix& other)
{
    self->preMult(other);
}

void postMult(osg::Matrix * self, const Matrix& other)
{
    self->postMult(other);
}
#endif
}

namespace PyOSG {
void init_matrix2(class_<Matrix> &matrix)
{
    matrix
        .def("mult", &osg::Matrix::mult)
#ifdef WIN32 // Generates ICE C1001
        .def("preMult", &preMult)
        .def("postMult", &postMult)
#else
        .def("preMult",
            (void (osg::Matrix::*)(const osg::Matrix&)) &osg::Matrix::preMult)
        .def("postMult",
            (void (osg::Matrix::*)(const osg::Matrix&)) &osg::Matrix::postMult)
#endif
        .def("identity",  &Matrix::identity)

        .def("scale", (Matrix (*)(const Vec3&)) &Matrix::scale)
        .def("scale", (Matrix (*)(Matrix::value_type, Matrix::value_type, Matrix::value_type)) &Matrix::scale)
        .def("translate", (Matrix (*)(const Vec3&)) &Matrix::translate)
        .def("translate", (Matrix (*)(Matrix::value_type, Matrix::value_type, Matrix::value_type)) &Matrix::translate)
        .def("rotate", (Matrix (*)(Matrix::value_type, Matrix::value_type, Matrix::value_type, Matrix::value_type)) &Matrix::rotate)
        .def("rotate", (Matrix (*)(Matrix::value_type, const Vec3&)) &Matrix::rotate)
        .def("rotate", (Matrix (*)(const Vec3&, const Vec3&)) &Matrix::rotate)
        .def("rotate", (Matrix (*)(Matrix::value_type, const Vec3&, Matrix::value_type, const Vec3&, Matrix::value_type, const Vec3&)) &Matrix::rotate)
        .def("rotate", (Matrix (*)(const Quat&)) &Matrix::rotate)
        .def("inverse",  &Matrix::inverse)
        .def("ortho",  &Matrix::ortho)
        .def("ortho2D",  &Matrix::ortho2D)
        .def("frustum",  &Matrix::frustum)
        .def("perspective",  &Matrix::perspective)
        .def("lookAt",  (Matrix(*)(const Vec3f&, const Vec3f&, const Vec3f&)) &Matrix::lookAt)
        .def("lookAt",  (Matrix(*)(const Vec3d&, const Vec3d&, const Vec3d&)) &Matrix::lookAt)

        .staticmethod("identity")
        .staticmethod("scale")
        .staticmethod("translate")
        .staticmethod("rotate")
        .staticmethod("inverse")
        .staticmethod("ortho")
        .staticmethod("ortho2D")
        .staticmethod("frustum")
        .staticmethod("perspective")
        .staticmethod("lookAt")
    ;
}
}

