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

#include <osgDB/ReadFile>

using namespace boost::python;
using namespace osgDB;

namespace PyOSG {
void init_ReadFile()
{
    def("readObjectFile",
        (osg::Object* (*)(const std::string&))
        &readObjectFile, return_internal_reference<>());
        // (function return type (path to functions) (function argument types) &address of function)

    def("readImageFile", 
        (osg::Image* (*)(const std::string&))
        &readImageFile, return_internal_reference<>());

    def("readNodeFile", 
        (osg::Node* (*)(const std::string&))
        &readNodeFile, return_internal_reference<>());

    def("readNodeFiles", 
        (osg::Node* (*)(std::vector<std::string>&))
        &readNodeFiles, return_internal_reference<>());

    def("readNodeFiles", 
        (osg::Node* (*)(osg::ArgumentParser&))
        &readNodeFiles, return_internal_reference<>());
}

}


