// Wrapper by Brett Hartshorn.  bhartshorn@opart.org
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

#include <boost/python/def.hpp>

#include <osgDB/WriteFile>

using namespace boost::python;

namespace {
bool writeObjectFile(osg::Object * obj, std::string filename)
{
    return osgDB::writeObjectFile(*obj, filename);
}

bool writeImageFile(osg::Image * image, std::string filename)
{
    return osgDB::writeImageFile(*image, filename);
}

bool writeNodeFile(osg::Node * node, std::string filename)
{
    return osgDB::writeNodeFile(*node, filename);
}

}

namespace PyOSG {

void init_WriteFile()
{
    def("writeObjectFile", &writeObjectFile);
    def("writeNodeFile", &writeNodeFile);
    def("writeImageFile", &writeImageFile);
}

}

