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
//

#include <boost/python.hpp>

using namespace boost::python;

namespace PyOSGViewer {

void init_ViewerBase();
void init_View();
void init_Viewer();
void init_ViewerEventHandlers();

void __init_osgViewer()
{
    init_ViewerBase();
    init_View();
    init_Viewer();
    init_ViewerEventHandlers();
}

} // namespace PyOSG

BOOST_PYTHON_MODULE(_osgViewer)
{
    scope().attr("__doc__") = "Wrapper for the OpenSceneGraph dbase scene graph library\n";
    PyOSGViewer::__init_osgViewer();
}

#include "module_tail.hpp"

