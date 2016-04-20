#include <boost/python.hpp>
#include <iostream>

#include "NodeVisitor.hpp"

using namespace boost::python;

namespace {
std::string NodeVisitor_str(osg::NodeVisitor * /* self */)
{
    std::ostringstream ost;
    ost << "NodeVisitor";
    return ost.str();
}

std::string NodeVisitor_repr(osg::NodeVisitor * /* self */)
{
    std::ostringstream ost;
    ost << "NodeVisitor";
    return ost.str();
}

list getNodePath(osg::NodeVisitor * self)
{
    list path;
    osg::NodePath nodePath = self->getNodePath();

    for (osg::NodePath::iterator iter=nodePath.begin(); iter < nodePath.end(); iter++) {
        path.append(*iter);
    }
    return path;
}

} // namespace

namespace PyOSG {

PY_OSG_DECL class_NodeVisitor * NodeVisitorClass = NULL;

void init_NodeVisitor()
{
    NodeVisitorClass = new class_NodeVisitor("NodeVisitor", 
            "Visitor for type safe operations on osg::Node's.\n"
            "Based on GOF's Visitor pattern. The NodeVisitor \n"
            "is useful for developing type safe operations to nodes\n"
            "in the scene graph (as per Visitor pattern), and adds to this\n"
            "support for optional scene graph traversal to allow\n"
            "operations to be applied to whole scenes at once. The Visitor\n"
            "pattern uses a technique of double dispatch as a mechanism to\n"
            "called the appropriate apply(..) method of the NodeVisitor.  To\n"
            "use this feature one must use the Node::accept(NodeVisitor) which\n"
            "is extended in each Node subclass, rather than the NodeVisitor\n"
            "apply directly.  So use root->accept(myVisitor); instead of\n"
            "myVisitor.apply(*root).  The later method will bypass the double\n"
            "dispatch and the appropriate NodeVisitor::apply(..) method will\n"
            "not be called.",
            no_init);

    scope nodevisitor_class(*NodeVisitorClass);

    (*NodeVisitorClass)
        .def(init<>())
        .def(init<osg::NodeVisitor::TraversalMode>())
        .def(init<osg::NodeVisitor::VisitorType, osg::NodeVisitor::TraversalMode>())
        .def("reset", &osg::NodeVisitor::reset)
        .def("setVisitorType", &osg::NodeVisitor::setVisitorType)
        .def("getVisitorType", &osg::NodeVisitor::getVisitorType)
        .def("setTraversalNumber", &osg::NodeVisitor::setTraversalNumber)
        .def("getTraversalNumber", &osg::NodeVisitor::getTraversalNumber)
        .def("setFrameStamp", &osg::NodeVisitor::setFrameStamp)
        .def("getFrameStamp", &osg::NodeVisitor::getFrameStamp, return_value_policy<manage_osg_object>())
        .def("setTraversalMask", &osg::NodeVisitor::setTraversalMask)
        .def("getTraversalMask", &osg::NodeVisitor::getTraversalMask)
        .def("setNodeMaskOverride", &osg::NodeVisitor::setNodeMaskOverride,
            "Set the NodeMaskOverride mask."
            "Used in validNodeMask() to determine whether to operate on a node or its "
            "subgraph, by OR'ing NodeVisitor::_nodeMaskOverride with the Node's own Node::_nodeMask."
            "Typically used to force on nodes which may have"
            "been switched off by their own Node::_nodeMask.*/"
            )
        .def("getNodeMaskOverride", &osg::NodeVisitor::getNodeMaskOverride,
            "Get the NodeMaskOverride mask.*/"
            )
#if 0   // FIXME Can't use because of private destructor of Node - need to fix
        .def("validNodeMask", &osg::NodeVisitor::validNodeMask,
            "Method to called by Node and its subclass' Node::accept() method, if the result is true"
            "to be used to cull operations of nodes and their subgraphs."
            "Return true if the result of a bit wise and of the NodeVisitor::_traversalMask"
            "with the bit or between NodeVistor::_nodeMaskOverride and the Node::_nodeMask."
            "default values for _traversalMask is 0xffffffff, _nodeMaskOverride is 0x0,"
            "and osg::Node::_nodeMask is 0xffffffff. */"
            )
#endif

        .def("setTraversalMode", &osg::NodeVisitor::setTraversalMode,
            "Set the traversal mode for Node::traverse() to use when "
            "deciding which children of a node to traverse. If a"
            "NodeVisitor has been attached via setTraverseVisitor()"
            "and the new mode is not TRAVERSE_VISITOR then the attached"
            "visitor is detached. Default mode is TRAVERSE_NONE.*/"
            )
        .def("getTraversalMode", &osg::NodeVisitor::getTraversalMode,
            "Get the traversal mode.*/"
            )
        .def("setUserData", &osg::NodeVisitor::setUserData)

        .def("traverse", &osg::NodeVisitor::traverse,
            "Method for handling traversal of a nodes."
            "If you intend to use the visitor for actively traversing "
            "the scene graph then make sure the accept() methods call"
            "this method unless they handle traversal directly.*/"
            )

        .def("pushOntoNodePath", &osg::NodeVisitor::pushOntoNodePath,
            "Method called by osg::Node::accept() method before"
            "a call the NodeVisitor::apply(..).  The back of the list will,"
            "therefore, be the current node being visited inside the apply(..),"
            "and the rest of the list will be the parental sequence of nodes "
            "from the top most node applied down the graph to the current node."
            "Note, the user does not typically call pushNodeOnPath() as it"
            "will be called automatically by the Node::accept() method.*/"
            )

        .def("popFromNodePath", &osg::NodeVisitor::popFromNodePath,
            "Method callby osg::Node::accept() method after"
            "a call the NodeVisitor::apply(..)."
            "Note, the user does not typically call pushNodeOnPath() as it"
            "will be called automatically by the Node::accept() method.*/"
            )

        .def("getNodePath",
            (const osg::NodePath&(osg::NodeVisitor::*)() const)&osg::NodeVisitor::getNodePath, return_value_policy<copy_const_reference>(),
            // &getNodePath,
            "Get the NodePath from the top most node applied down"
            "to the current Node being visited.*/"
            )

        .def("getEyePoint", &osg::NodeVisitor::getEyePoint)

        .def("getDistanceToEyePoint", &osg::NodeVisitor::getDistanceToEyePoint)

        .def("getDistanceFromEyePoint", &osg::NodeVisitor::getDistanceFromEyePoint)
#if 0
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Node&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Geode&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Billboard&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Group&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Projection&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::CoordinateSystemNode&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::ClipNode&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::LightSource&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Transform&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::MatrixTransform&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::PositionAttitudeTransform&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Switch&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Sequence&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::LOD&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::PagedLOD&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::Impostor&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::ClearNode&))
        &osg::NodeVisitor::apply)
        .def("apply", 
        (void (osg::NodeVisitor::*)(osg::OccluderNode&))
        &osg::NodeVisitor::apply)
#endif

        .def("__str__",  &NodeVisitor_str)
        .def("__repr__", &NodeVisitor_repr)
        ;

#   define OSG_ENUM(VALUE) mode.value(#VALUE, osg::NodeVisitor::VALUE)
    enum_<osg::NodeVisitor::TraversalMode> mode("TraversalMode");
    OSG_ENUM(TRAVERSE_NONE);
    OSG_ENUM(TRAVERSE_PARENTS);
    OSG_ENUM(TRAVERSE_ALL_CHILDREN);
    OSG_ENUM(TRAVERSE_ACTIVE_CHILDREN);
    mode.export_values();
#   undef OSG_ENUM

#   define OSG_ENUM(VALUE) type.value(#VALUE, osg::NodeVisitor::VALUE)
    enum_<osg::NodeVisitor::VisitorType> type("VisitorType");
    OSG_ENUM(NODE_VISITOR);
    OSG_ENUM(UPDATE_VISITOR);
    OSG_ENUM(COLLECT_OCCLUDER_VISITOR);
    OSG_ENUM(CULL_VISITOR);
    type.export_values();
#   undef OSG_ENUM
}
} // namespace PyOSG

