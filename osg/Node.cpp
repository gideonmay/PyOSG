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

#include <boost/python/class.hpp>
#include <boost/python/call.hpp>
#include <boost/python/call_method.hpp>
#include <boost/python/ptr.hpp>
#include <boost/python/list.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/object.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/iterator.hpp>
#include <boost/ref.hpp>

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Billboard>
#include <osg/Transform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/LOD>

#include <string>
#include <iostream>

#include "Node.hpp"

using namespace boost::python;

namespace {
class NodeCallback : public osg::NodeCallback {
    public :
        NodeCallback(PyObject * cb) {
            _ncallback = cb; 
            Py_XINCREF(_ncallback);
        }

        ~NodeCallback()
        {
            Py_XDECREF(_ncallback);
        }

        virtual void operator() (osg::Node * node, osg::NodeVisitor * nv)
        {
            try {
                call_method<void>(_ncallback, "apply", ptr(node), ptr(nv));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
                return;
            }
            traverse(node, nv);
        }
    private :
        PyObject * _ncallback;
};


void osgNode_setUpdateCallback(osg::Node * self, PyObject * cb)
{
    // is_nodecallback is true if the cb is a direct derived class from osg::NodeCallback
    // if it is 0, then it's a python defined class
    bool is_nodecallback = extract<osg::NodeCallback *>(cb).check();

    Py_XINCREF(cb); // FIXME Memory leak, on node dtor should decref the cb object

    // if it is a c++ class or derived from the c++ class set the node callback directly
    if (is_nodecallback) { // create a wrapper object and call the python method
        extract<osg::NodeCallback *> callback(cb);
        self->setUpdateCallback(callback);
    } else {
        NodeCallback * callback = new NodeCallback(cb); // another memory leak, the python object isn't deleted
        self->setUpdateCallback(callback);
    }
}

void osgNode_setCullCallback(osg::Node * self, PyObject * cb)
{
    // is_nodecallback is true if the cb is a direct derived class from osg::NodeCallback
    // if it is 0, then it's a python defined class
    bool is_nodecallback = extract<osg::NodeCallback *>(cb).check();

    Py_XINCREF(cb); // FIXME Memory leak, on node dtor should decref the cb object

    // if it is a c++ class, set the node callback directly
    if (is_nodecallback) {
        extract<osg::NodeCallback *> callback(cb);
        self->setCullCallback(callback);
    } else {
        NodeCallback * callback = new NodeCallback(cb); // another memory leak, the python object isn't deleted
        self->setCullCallback(callback);
    }
}

const std::string& getDescription(osg::Node * self, unsigned int i)
{
    return self->getDescription(i);
}

list getDescriptions(osg::Node * self)
{
    list desc;
    osg::Node::DescriptionList desclist = self->getDescriptions();

    for (osg::Node::DescriptionList::iterator iter=desclist.begin(); iter < desclist.end(); iter++) {
        desc.append(*iter);
    }
    return desc;
}

} // namespace

namespace PyOSG {

class_Node * NodeClass = NULL;

void init_Node()
{

    class_<osg::NodePath>("NodePath")
        .def("__iter__", iterator<osg::NodePath, return_value_policy<manage_osg_object> >())
        .def("__len__", &osg::NodePath::size)
        ;

    NodeClass = new class_Node("Node",
            "Base class for all internal nodes in the scene graph.\n"
            "Provides interface for most common node operations (Composite Pattern).\n", no_init);

    scope node_scope(*NodeClass);

    (*NodeClass)
        .def(init<>())
        .def("accept", &osg::Node::accept,
            "Visitor Pattern : calls the apply method of a NodeVisitor with this node's type.")
        .def("ascend", &osg::Node::ascend,
            "Traverse upwards : calls parents' accept method with NodeVisitor.")
        .def("traverse", &osg::Node::traverse,
            "Traverse downwards : calls children's accept method with NodeVisitor.")

        .def("setName", (void (osg::Node::*)(const std::string &)) &osg::Node::setName,
            "Set the name of node.\n")
        .def("getName", &osg::Node::getName, return_value_policy<copy_const_reference>(),
            "Get the name of node.\n")

        .def("getParents", (osg::Node::ParentList(osg::Node::*)()) &osg::Node::getParents)

        .def("getParent", 
             (osg::Group *(osg::Node::*)(unsigned int))&osg::Node::getParent, 
             return_value_policy<manage_osg_object>(),
             " Get a single const parent of node.\n"
             " param i index of the parent to get.\n"
             " return the parent i.\n")

        .def("getNumParents", &osg::Node::getNumParents,
             "Get the number of parents of node.\n"
             "return the number of parents of this node.\n")

        .def("setUpdateCallback", &osgNode_setUpdateCallback,
            "Set app node callback, called during app traversal.\n")

        /** Get app node callback, called during app traversal. */
        //inline NodeCallback* getUpdateCallback() { return _appCallback.get(); }

        .def("getNumChildrenRequiringUpdateTraversal", &osg::Node::getNumChildrenRequiringUpdateTraversal,
            "Get the number of Children of this node which require App traversal,\n"
            "since they have an UpdateCallback attached to them or their children.*/\n")

        .def("setCullCallback", &osgNode_setCullCallback,
            "Set cull node callback, called during cull traversal.\n")

        /** Get app node callback, called during app traversal. */
        //inline NodeCallback* getCullCallback() { return _cullCallback.get(); }

        .def("setCullingActive", &osg::Node::setCullingActive,
            "Set the view frustum/small feature culling of this node to be active or inactive.\n"
            "The default value to true for _cullingActive. Used a guide\n"
            "to the cull traversal.\n")

        .def("getCullingActive", &osg::Node::getCullingActive,
            "Get the view frustum/small feature _cullingActive flag for this node. Used a guide\n"
            "to the cull traversal.\n")

        .def("getNumChildrenWithCullingDisabled", &osg::Node::getNumChildrenWithCullingDisabled,
            "Get the number of Children of this node which have culling disabled.*/\n")

        .def("isCullingActive", &osg::Node::isCullingActive,
            "Return true if this node can be culled by view frustum, occlusion or small feature culling during the cull traversal.\n"
            "note, return true only if no children have culling disabled, and the local _cullingActive flag is true.*/\n")

        .def("getNumChildrenWithOccluderNodes", &osg::Node::getNumChildrenWithOccluderNodes,
            "Get the number of Children of this node which are or have OccluderNode's.*/\n")

        .def("containsOccluderNodes", &osg::Node::containsOccluderNodes,
            "return true if this node is an OccluderNode or the subgraph below this node are OccluderNodes.*/\n")

        .def("setNodeMask", &osg::Node::setNodeMask,
            "Set the node mask. Note, node mask is will be replaced by TraversalMask.\n")
        .def("getNodeMask", &osg::Node::getNodeMask,
            "Get the node Mask. Note, node mask is will be replaced by TraversalMask.\n")

        .def("getDescriptions", &getDescriptions,
            "Get the description list of the const node.")
        .def("getDescription", &getDescription, return_value_policy<copy_const_reference>(),
            "Get a single description of the node.")
        .def("getNumDescriptions", &osg::Node::getNumDescriptions,
            "Get the number of descriptions of the node.")
        .def("addDescription", &osg::Node::addDescription,
            "Add a description string to the node.")

        //.def("setStateSet", &osg::Node::setStateSet,
        //    "set the node's StateSet.\n")
        .def("getOrCreateStateSet", 
            (osg::StateSet *(osg::Node::*)(void)) &osg::Node::getOrCreateStateSet,
            return_value_policy<manage_osg_object>(),
            "return the node's StateSet, if one does not already exist create it\n"
            "set the node and return the newly created StateSet. This ensures\n"
            "that a valid StateSet is always returned and can be used directly.\n")
        .def("getStateSet",
            (osg::StateSet *(osg::Node::*)(void)) &osg::Node::getStateSet,
            return_value_policy<manage_osg_object>(),
            "return the node's StateSet. returns None if a stateset is not attached.\n")

        .def("getBound", &osg::Node::getBound, return_value_policy<copy_const_reference>(),
            "get the bounding sphere of node.\n"
            "Using lazy evaluation computes the bounding sphere if it is 'dirty'.\n")

        .def("dirtyBound", &osg::Node::dirtyBound,
            "Mark this node's bounding sphere dirty.\n"
            "Forcing it to be computed on the next call to getBound().\n")
         ;

    scope();

}
}
