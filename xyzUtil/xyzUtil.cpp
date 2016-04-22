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
#include "OffScreenRendererPBuffer.h"

using namespace boost::python;
using namespace OsgTools;

namespace {
    void __init__OffScreenRendererPBuffer() {
        class_<OffScreenRendererPBuffer, boost::noncopyable> offscreenrenderer("OffScreenRenderer", no_init);

        offscreenrenderer
            .def(init<unsigned int, unsigned int>())
            .def("scene",
                &OffScreenRendererPBuffer::scene)
                .def("viewMatrix",
                     &OffScreenRendererPBuffer::viewMatrix)
            .def("render",
                &OffScreenRendererPBuffer::render)
            .def("writeImageFile",
                &OffScreenRendererPBuffer::writeImageFile)
                ;
    }
}

namespace PyOSGViewer {

void __init_xyzUtil()
{
    __init__OffScreenRendererPBuffer();
}

} // namespace PyOSG

BOOST_PYTHON_MODULE(_xyzUtil)
{
    scope().attr("__doc__") = "\n";
    PyOSGViewer::__init_xyzUtil();
}

#include "module_tail.hpp"

