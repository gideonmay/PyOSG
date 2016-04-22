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

#include <osg/ArgumentParser>

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

osg::ArgumentParser * construct_from_list(list& l)
{
    int * argc = new int;
    * argc = len(l);

    char ** argv;
    argv = new char* [*argc];
    for (int a = 0; a<*argc ; a++) {
        char * arg = extract<char *>(l[a]);
        argv[a] = new char [strlen(arg) + 1];
        strcpy(argv[a], arg);
    }


    osg::ArgumentParser * parser = new osg::ArgumentParser(argc, argv);

    return parser;
}

std::string getitem(osg::ArgumentParser& parser, int pos)
{
    if (parser.argc() <= pos) {
        PyErr_SetString(PyExc_IndexError, "assignment index out of range");
        throw_error_already_set();
    }
    return std::string(parser[pos]);
}

bool errors_0(osg::ArgumentParser& parser) { return parser.errors(); }
bool errors_1(osg::ArgumentParser& parser, osg::ArgumentParser::ErrorSeverity severity) { return parser.errors(severity); }

void reportRemainingOptionsAsUnrecognized_0(osg::ArgumentParser& parser) {
    parser.reportRemainingOptionsAsUnrecognized();
}

void reportRemainingOptionsAsUnrecognized_1(osg::ArgumentParser& parser, osg::ArgumentParser::ErrorSeverity severity) {
    parser.reportRemainingOptionsAsUnrecognized(severity);
}

void writeErrorMessages_0(osg::ArgumentParser& parser) {
    return parser.writeErrorMessages(std::cout);
}

void writeErrorMessages_1(osg::ArgumentParser& parser, osg::ArgumentParser::ErrorSeverity severity) {
    return parser.writeErrorMessages(std::cout, severity);
}

void writeErrorMessages_2(osg::ArgumentParser& parser, PyObject * fobj) {
    if (!PyFile_Check(fobj)) {
      throw boost::python::error_already_set();
    }

    std::FILE * file = PyFile_AsFile(fobj);
    // file = stderr;
    std_obuf buf(file);
    std::ostream os(&buf);

    return parser.writeErrorMessages(os);
}

void writeErrorMessages_3(osg::ArgumentParser& parser, PyObject * fobj, osg::ArgumentParser::ErrorSeverity severity) {
    if (!PyFile_Check(fobj)) {
      throw boost::python::error_already_set();
    }

    std::FILE * file = PyFile_AsFile(fobj);
    // file = stderr;
    std_obuf buf(file);
    std::ostream os(&buf);

    return parser.writeErrorMessages(os, severity);
}

} // namespace

namespace PyOSG {

void init_ArgumentParser()
{
    class_<osg::ArgumentParser, boost::noncopyable> arg_parser("ArgumentParser", no_init);

    scope arg_parser_scope(arg_parser);

    arg_parser
        .def("__init__", make_constructor(&construct_from_list))

        .def("setApplicationUsage", 
            &osg::ArgumentParser::setApplicationUsage)

        .def("getApplicationUsage",
            (osg::ApplicationUsage* (osg::ArgumentParser::*)())
            &osg::ArgumentParser::getApplicationUsage,
            return_internal_reference<>())
        .def("argc", 
            &osg::ArgumentParser::argc,
            return_value_policy<copy_non_const_reference>(),
            "return the argument count.")

        .def("__getitem__",
            (std::string (*)(osg::ArgumentParser&, int))
            &getitem,
            "return the string argument at the specified position.")
        .def("getApplicationName", 
            &osg::ArgumentParser::getApplicationName,
            "return the application name, as specified by argv[0]")

        .def("find", 
            &osg::ArgumentParser::find)

        .def("match", 
            &osg::ArgumentParser::match)

        .def("isOption",
            (bool (osg::ArgumentParser::*)(int) const)
            &osg::ArgumentParser::isOption)
        .def("isString",
            (bool (osg::ArgumentParser::*)(int) const)
            &osg::ArgumentParser::isString)
        .def("isNumber",
            (bool (osg::ArgumentParser::*)(int) const)
            &osg::ArgumentParser::isNumber)

        .def("containsOptions",
            &osg::ArgumentParser::containsOptions)

        .def("remove",
            &osg::ArgumentParser::remove)

        .def("read",
            (bool (osg::ArgumentParser::*)(const std::string& ))
            &osg::ArgumentParser::read,
            "search for an occurance of a string in the argument list, on sucess\n"
            "remove that occurance from the list and return true, otherwise return false.\n")

        .def("errors", 
            &errors_0,
            "return the error flag, true if an error has occured when reading arguments.")

        .def("errors", 
            &errors_1,
            "return the error flag, true if an error has occured when reading arguments.")


        .def("reportRemainingOptionsAsUnrecognized", 
            &reportRemainingOptionsAsUnrecognized_0,
            "for each remaining option report it as an unrecongnized.")
        .def("reportRemainingOptionsAsUnrecognized", 
            &reportRemainingOptionsAsUnrecognized_1,
            "for each remaining option report it as an unrecongnized.")

        .def("writeErrorMessages", 
            &writeErrorMessages_0,
            "write out error messages at an above specified .\n")
        .def("writeErrorMessages", 
            &writeErrorMessages_1,
            "write out error messages at an above specified .\n")
        .def("writeErrorMessages", 
            &writeErrorMessages_2,
            "write out error messages at an above specified .\n")
        .def("writeErrorMessages", 
            &writeErrorMessages_3,
            "write out error messages at an above specified .\n")
        ;


#   define OSG_ENUM_ERROR(VALUE) error.value(#VALUE, osg::ArgumentParser::VALUE)
    enum_<osg::ArgumentParser::ErrorSeverity> error("ErrorSeverity");
    OSG_ENUM_ERROR(BENIGN);
    OSG_ENUM_ERROR(CRITICAL);
    error.export_values();
}
} // namespace PyOSG
