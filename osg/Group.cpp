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

#include <osg/Group>

#include <string>
#include <iostream>

#include "Node.hpp"
#include "Group.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
DEFINE_NODE_CAST(Group)

bool removeChild(osg::Group * group, unsigned int pos)
{
    return group->removeChild(pos);
}

class GroupBase : public osg::Group {
  public:
    GroupBase() : osg::Group() {}
};

// Class which can be derived in Python with the method traverse overriden.
class GroupBase_imp : public GroupBase {
  public:
    GroupBase_imp(PyObject * p) : GroupBase(),  _self(p) {
        Py_XINCREF(_self);
    }

    ~GroupBase_imp() {
        Py_XDECREF(_self);
    }

   virtual void traverse(osg::NodeVisitor& nv) {
        try {
            call_method<void>(_self, "traverse", ptr(&nv));
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
    }

    virtual void traverse_imp(osg::NodeVisitor& nv) {
        osg::Group::traverse(nv);
    }

  private:
      PyObject * _self;
};

}

namespace PyOSG {

class_Group * GroupClass = NULL;

void init_Group()
{
    // class_<osg::Group::ChildList >("ChildList") .def("__iter__", iterator<osg::Group::ChildList, return_internal_reference<>() >());

    REGISTER_NODE_CAST(Group)

    GroupClass = new class_Group("Group",
             "General group node which maintains a list of children.\n"
             "Children are reference counted. This allows children to be shared\n"
             "with memory management handled automatically via osg::Referenced.\n",
             no_init);

    (*GroupClass)
        .def(init<>())
        .def("addChild", &osg::Group::addChild,
            "addChild(child) -> status\n"
            "\n"
            "Add Node to Group.\n"
            "If child is not None and is not contained in Group then increment its  \n"
            "reference count, add it to the child list and dirty the bounding \n"
            "sphere to force it to recompute on next getBound() and return true for success.\n"
            "Otherwise return false. Scene nodes can't be added as child nodes.\n")

        .def("insertChild", &osg::Group::insertChild)

        .def("removeChild", &removeChild)

        .def("removeChild", (bool (osg::Group::*) (unsigned int, unsigned int)) &osg::Group::removeChild)

        .def("removeChild", (bool (osg::Group::*) (osg::Node *)) &osg::Group::removeChild,
            "removeChild(child) -> status\n"
            "\n"
            "Remove Node from Group.\n"
            "If child is contained in Group then remove it from the child\n"
            "list, decrement its reference count, and dirty the \n"
            "bounding sphere to force it to recompute on next getBound() and\n"
            "return true for success.  If Node is not found then return false\n"
            "and do not change the reference count of the Node.\n")

        .def("replaceChild", &osg::Group::replaceChild,
            "replaceChild(origChild, newChild) -> status\n"
            "\n"
            "Replace specified Node with another Node.\n"
            "Decrement the reference count origNode and increments the\n"
            "reference count of newNode, and dirty the bounding sphere\n"
            "to force it to recompute on next getBound() and returns true.\n"
            "If origNode is not found then return false and do not \n"
            "add newNode.  If newNode is NULL then return false and do\n"
            "not remove origNode. Also returns false if newChild is a Scene node.\n")

        .def("getNumChildren", &osg::Group::getNumChildren,
            "getNumChildren() -> count\n"
            "\n"
            "return the number of chilren nodes.")

        .def("setChild", &osg::Group::setChild)

        .def("getChild",
            (osg::Node *(osg::Group::*)(unsigned int))&osg::Group::getChild,
            return_value_policy<manage_osg_object>(),
            "getChild(i) -> node\n"
            "\n"
            "return child node at position i.")

        .def("containsNode", &osg::Group::containsNode,
            "containsNode(node) -> status\n"
            "\n"
            "return true if node is contained within Group.")

        .def("getChildIndex", &osg::Group::getChildIndex)
        ;

    class_<GroupBase, osg::ref_ptr<GroupBase_imp>, bases<osg::Group>, boost::noncopyable> group_base("Group_base",
        "General group node which maintains a list of children.\n"
        "Children are reference counted. This allows children to be shared\n"
        "with memory management handled automatically via osg::Referenced.\n",
        no_init);

    group_base
        .def(init<>())
        .def("traverse",
            &GroupBase_imp::traverse_imp)
        ;
}
}
