#ifndef PYOSG_ARGUMENT_PARSER
#define PYOSG_ARGUMENT_PARSER 1

#include <boost/python/list.hpp>

#include <osg/ArgumentParser>
#include <osg/ApplicationUsage>

#include <string>

namespace PyOSG {

using namespace boost::python;

class ArgumentParser : public  osg::ArgumentParser {
  public:
    ArgumentParser(list& );
    ArgumentParser(int * argc, char ** argv) : osg::ArgumentParser(argc, argv) {}
    ~ArgumentParser();

    // void setApplicationUsage(osg::ApplicationUsage* usage) { _ap->setApplicationUsage(usage); }


    osg::ApplicationUsage* getApplicationUsage() {
        return osg::ArgumentParser::getApplicationUsage(); 
    }

    int argc() {
        return osg::ArgumentParser::argc();
    }

    // std::string getApplicationName() { return _ap->getApplicationName(); }

    bool read(const std::string& str) {
        return osg::ArgumentParser::read(str);
    }

    bool errors_0() { return errors(); }
    bool errors_1(osg::ArgumentParser::ErrorSeverity severity) { return errors(severity); }

    void reportRemainingOptionsAsUnrecognized_0() {
        reportRemainingOptionsAsUnrecognized();
    }

    void reportRemainingOptionsAsUnrecognized_1(osg::ArgumentParser::ErrorSeverity severity) {
        reportRemainingOptionsAsUnrecognized(severity);
    }

    void writeErrorMessages_0() {
        return writeErrorMessages(std::cout); 
    }

    void writeErrorMessages_1(osg::ArgumentParser::ErrorSeverity severity) {
        return writeErrorMessages(std::cout, severity); 
    }

    osg::ArgumentParser& argumentParser() { return *this; }

    std::string getitem(int pos)
    {
        if (_startArgc <= pos) {
            PyErr_SetString(PyExc_IndexError, "assignment index out of range");
            throw_error_already_set();
        }
        return std::string((*this)[pos]);
    }

  protected :
    int                     _totArgc;
    int                     _startArgc;
};

} // namespace PyOSG

#endif // PYOSG_ARGUMENT_PARSER

