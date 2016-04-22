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

#include <osg/ApplicationUsage>

#include <iostream>
#include "held_ptr.hpp"

using namespace boost::python;

namespace {

class std_obuf: public std::streambuf {
  public:
    std_obuf(std::FILE* file): _file(file) {}
  protected:
    std::streambuf::int_type overflow(std::streambuf::int_type c) {
        return std::fputc(c, _file) ==EOF? std::streambuf::traits_type::eof(): c;
    }
    FILE* _file;
};

void MyWrite_1(osg::ApplicationUsage& _au)
{
    _au.write(std::cout);
}
void MyWrite_2(osg::ApplicationUsage& _au, unsigned int type)
{
    _au.write(std::cout, type);
}
void MyWrite_3(osg::ApplicationUsage& _au, unsigned int type, unsigned int width)
{
    _au.write(std::cout, type, width);
}

void MyWrite_4(osg::ApplicationUsage& _au, PyObject *  fobj )
{
    if (!PyFile_Check(fobj)) {
      throw boost::python::error_already_set();
    }

    std::FILE * file = PyFile_AsFile(fobj);
    std_obuf buf(file);
    std::ostream os(&buf);

    _au.write(os);
}

void MyWrite_5(osg::ApplicationUsage& _au, PyObject *  fobj, unsigned int type )
{
    if (!PyFile_Check(fobj)) {
      throw boost::python::error_already_set();
    }

    std::FILE * file = PyFile_AsFile(fobj);
    std_obuf buf(file);
    std::ostream os(&buf);

    _au.write(os, type);
}

dict getCommandLineOptions(osg::ApplicationUsage& _au)
{
    dict options;

    osg::ApplicationUsage::UsageMap::const_iterator citr;
    for(citr=_au.getCommandLineOptions().begin();
        citr!=_au.getCommandLineOptions().end();
        ++citr)
    {
        options[citr->first] = citr->second;
    }
    return options;
}

dict getEnvironmentalVariables(osg::ApplicationUsage& _au)
{
    dict options;

    osg::ApplicationUsage::UsageMap::const_iterator citr;
    for(citr=_au.getEnvironmentalVariables().begin();
        citr!=_au.getEnvironmentalVariables().end();
        ++citr)
    {
        options[citr->first] = citr->second;
    }
    return options;
}

dict getKeyboardMouseBindings(osg::ApplicationUsage& _au)
{
    dict options;

    osg::ApplicationUsage::UsageMap::const_iterator citr;
    for(citr=_au.getKeyboardMouseBindings().begin();
        citr!=_au.getKeyboardMouseBindings().end();
        ++citr)
    {
        options[citr->first] = citr->second;
    }
    return options;
}

void addCommandLineOption(osg::ApplicationUsage& _au, const std::string& option,const std::string& explanation)
{
    _au.addCommandLineOption(option, explanation);
}
}

namespace PyOSG {

void init_ApplicationUsage()
{
    class_<osg::ApplicationUsage, osg::ref_ptr<osg::ApplicationUsage>, boost::noncopyable>
            app_usage("ApplicationUsage", no_init);

    app_usage
        .def(init<>())
        .def(init<const std::string&>())

        .def("setApplicationName",
            &osg::ApplicationUsage::setApplicationName)
        .def("getApplicationName",
            &osg::ApplicationUsage::getApplicationName,
            return_value_policy<copy_const_reference>())

        .def("setDescription", 
            &osg::ApplicationUsage::setDescription)
        .def("getDescription", 
            &osg::ApplicationUsage::getDescription,
            return_value_policy<copy_const_reference>())

        .def("addUsageExplanation", 
            &osg::ApplicationUsage::addUsageExplanation)

        .def("setCommandLineUsage", 
            &osg::ApplicationUsage::setCommandLineUsage)
        .def("getCommandLineUsage", 
            &osg::ApplicationUsage::getCommandLineUsage,
            return_value_policy<copy_const_reference>())

        .def("addCommandLineOption", 
            &addCommandLineOption)
        .def("addCommandLineOption", 
            &osg::ApplicationUsage::addCommandLineOption)
        .def("getCommandLineOptions", 
            &getCommandLineOptions)

        .def("addEnvironmentalVariable", 
            &osg::ApplicationUsage::addEnvironmentalVariable)
        .def("getEnvironmentalVariables", 
            &getEnvironmentalVariables)

//        .def("addKeyboardMouseBinding",
//            &osg::ApplicationUsage::addKeyboardMouseBinding)
        .def("getKeyboardMouseBindings", 
            &getKeyboardMouseBindings)

        .def("getFormattedString", 
            &osg::ApplicationUsage::getFormattedString)

        .def("write",
            &MyWrite_1)
        .def("write",
            &MyWrite_2)
        .def("write",
            &MyWrite_3)
        .def("write",
            &MyWrite_4)
        .def("write",
            &MyWrite_5)
        ;

    scope app_usage_scope(app_usage);

    enum_<osg::ApplicationUsage::Type> app_type("ApplicationUsage_Type");
#   define OSG_ENUM_TYPE(VALUE) app_type.value(#VALUE, osg::ApplicationUsage::VALUE)
    OSG_ENUM_TYPE(COMMAND_LINE_OPTION);
    OSG_ENUM_TYPE(ENVIRONMENTAL_VARIABLE);
    OSG_ENUM_TYPE(KEYBOARD_MOUSE_BINDING);
    app_type.export_values();

    // TODO, missing class ApplicationUsageProxy
}
} // namespace PyOSG
