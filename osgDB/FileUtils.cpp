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

#include <iostream>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/FileUtils>

using namespace boost::python;
using namespace osgDB;

namespace {

std::string findDataFile_1(const std::string& filename)
{
    return osgDB::findDataFile(filename);
}

void addDataFilePath(const std::string& path)
{
    osgDB::FilePathList& pathList = osgDB::getDataFilePathList();
    pathList.push_back(path);
}

} // namespace

namespace PyOSG {

void init_FileUtils()
{
    def("findDataFile",
        (std::string (*) (const std::string&,osgDB::CaseSensitivity)) &osgDB::findDataFile,
        "Search for specified file in file system, checking the DataFilePathList for possible paths,\n"
        "returning the full path of the first valid file found, return an empty string if no string is found.\n");

    def("findDataFile", &findDataFile_1);

    def("setDataFilePathList",
        (void (*)(const std::string&)) &osgDB::setDataFilePathList);

    def("addDataFilePath", &addDataFilePath);

#   define OSG_ENUM_CSENSE(VALUE) csense.value(#VALUE, osgDB::VALUE)
    enum_<osgDB::CaseSensitivity> csense("CaseSensitivity");
    OSG_ENUM_CSENSE(CASE_SENSITIVE);
    OSG_ENUM_CSENSE(CASE_INSENSITIVE);
    csense.export_values();

#   define OSG_ENUM_FILETYPE(VALUE) filetype.value(#VALUE, osgDB::VALUE)
    enum_<osgDB::FileType> filetype("FileType");
    OSG_ENUM_FILETYPE(FILE_NOT_FOUND);
    OSG_ENUM_FILETYPE(REGULAR_FILE);
    OSG_ENUM_FILETYPE(DIRECTORY);
    filetype.export_values();
}

}
