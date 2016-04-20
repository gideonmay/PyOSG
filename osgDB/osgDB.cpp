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
#include <boost/python/detail/api_placeholder.hpp>

#include <string>
#include <iostream>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/Registry>
#include <osgDB/FileUtils>

using namespace boost::python;

namespace PyOSG {

    void init_ReadFile();
    void init_WriteFile();
    void init_Registry();
    void init_FileUtils();

}

using namespace PyOSG;

namespace {


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4927)   // FIXME
#endif

std::string extract_string(object x)
{
    std::string s = extract<std::string>(x);
    return s;
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

bool osgDB_writeObjectFile(osg::Object * obj, std::string filename)
{
    return osgDB::writeObjectFile(*obj, filename);
}

bool osgDB_writeImageFile(osg::Image * image, std::string filename)
{
    return osgDB::writeImageFile(*image, filename);
}

bool osgDB_writeNodeFile(osg::Node * node, std::string filename)
{
    return osgDB::writeNodeFile(*node, filename);
}


#if 0
void osgDB_readCommandLine(list & cline)
{
    std::vector<std::string> cmdline;
    for (int i=0; i < len(cline); i++) {
        // eat each commandline option
        std::string str = extract_string(cline.pop(0));
        cmdline.push_back(str);
    }
    // cline is empty by now

    // do the actual read
    osgDB::readCommandLine(cmdline);

    std::vector<std::string>::iterator itr = cmdline.begin();
    for(;itr!=cmdline.end();++itr) {
        // now append the nonused options
        cline.append(*itr);
    }
}
#endif

osg::Node * readNodeFiles_1(osg::ArgumentParser& parser)
{
    return osgDB::readNodeFiles(parser);
}

osg::Node * readNodeFiles_2(osg::ArgumentParser& parser, const osgDB::ReaderWriter::Options *  options)
{
    return osgDB::readNodeFiles(parser, options);
}

osg::Node * readNodeFiles_3(list & files)
{
    std::vector<std::string> cmdline;
    for (int i=0; i<len(files); i++) {
        std::string str = extract_string(files[i]);
        cmdline.push_back(str);
    }
    return osgDB::readNodeFiles(cmdline);
}


}


namespace PyOSG {

BOOST_PYTHON_FUNCTION_OVERLOADS(readImageFile_overloads, osgDB::readImageFile, 1, 2);
BOOST_PYTHON_FUNCTION_OVERLOADS(readNodeFile_overloads, osgDB::readNodeFile, 1, 2);
BOOST_PYTHON_FUNCTION_OVERLOADS(readObjectFile_overloads, osgDB::readObjectFile, 1, 2);

void __init_osgDB()
{
    init_ReadFile();
    init_WriteFile();
    init_Registry();
    init_FileUtils();

    def("readObjectFile", 
        (osg::Object*(*)(const std::string&))
        &osgDB::readObjectFile,
        return_internal_reference<>());
    def("readImageFile", 
        (osg::Image *(*)(const std::string&))
        &osgDB::readImageFile,
        return_internal_reference<>());
    def("readNodeFile", 
        (osg::Node*(*)(const std::string& filename))
        &osgDB::readNodeFile,
        return_internal_reference<>());


    def("readNodeFiles", &readNodeFiles_1, return_internal_reference<>());
    def("readNodeFiles", &readNodeFiles_2, return_internal_reference<>());
    def("readNodeFiles", &readNodeFiles_3, return_internal_reference<>());

    def("writeObjectFile", &osgDB_writeObjectFile);
    def("writeImageFile", &osgDB_writeImageFile);
    def("writeNodeFile", &osgDB_writeNodeFile);

    scope().attr("__module__") = "PyOSG.osgDB";
    scope().attr("__name__") = "PyOSG.osgDB";

    // def("readCommandLine", &osgDB_readCommandLine);

#if defined WIN32
    osgDB::getLibraryFilePathList().push_back("Bin/osgDB/");
    osgDB::getLibraryFilePathList().push_back("DLLs/osgDB/");
#endif
}
}

BOOST_PYTHON_MODULE(_osgDB)
{
    PyOSG::__init_osgDB();
}
#include "module_tail.hpp"
