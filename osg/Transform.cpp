#include <boost/python.hpp>

#include <osg/Transform>

#include <string>
#include <iostream>

#include "Node.hpp"
#include "Transform.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {
DEFINE_NODE_CAST(Transform)
} // namespace

namespace PyOSG {

class TransformBase : public osg::Transform {
  public:
    TransformBase() : osg::Transform() {}
};

// Class which can be derived in Python with the methods computeLocalToWorld and
// computeWorldToLocal overriden.
class TransformBase_imp : public TransformBase {
  public:
    TransformBase_imp(PyObject * p) :
      TransformBase(),  _self(p),
      _has_cWTL(-1), _has_cLTW(-1) {
        Py_XINCREF(_self);
    }

    ~TransformBase_imp() {
        Py_XDECREF(_self);
    }

    virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        // cache if the python class has computeLocalToWorldMatrix implemented
        if (_has_cLTW == -1) {
            if (PyObject_HasAttrString(_self, "computeLocalToWorldMatrix")) {
                _has_cLTW = 1;
            } else {
                _has_cLTW = 0;
            }
        }

        bool ret = false;
        if (_has_cLTW) {
            try {
                ret = call_method<int>(_self, "computeLocalToWorldMatrix", ptr(&matrix), ptr(nv));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        } else {
            ret = osg::Transform::computeLocalToWorldMatrix(matrix, nv);
        }

        return  ret;
    }

    virtual bool computeLocalToWorldMatrix_imp(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        return osg::Transform::computeLocalToWorldMatrix(matrix, nv);
    }

    virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        if (_has_cWTL == -1) {
            if (PyObject_HasAttrString(_self, "computeWorldToLocalMatrix")) {
                _has_cWTL = 1;
            } else {
                _has_cWTL = 0;
            }
        }

        bool ret = false;
        if (_has_cLTW) {
            try {
                ret = call_method<int>(_self, "computeWorldToLocalMatrix", ptr(&matrix), ptr(nv));
            } catch(...) {
                handle_exception();
                PyErr_Print();
                throw_error_already_set();
            }
        } else {
            ret = osg::Transform::computeWorldToLocalMatrix(matrix, nv);
        }
        return  ret;
    }

    virtual bool computeWorldToLocalMatrix_imp(osg::Matrix& matrix, osg::NodeVisitor* nv) const
    {
        return Transform::computeWorldToLocalMatrix(matrix, nv);
    }

  private:
      PyObject * _self;
      mutable int       _has_cWTL;
      mutable int       _has_cLTW;
};

class_Transform * TransformClass = NULL;

void init_Transform()
{
    def("computeLocalToWorld",
        &osg::computeLocalToWorld,
        "Compute the matrix which transforms objects in local coords to world coords,\n"
        "by accumulating the Transform local to world matrices along the specified node path.\n");

    def("computeWorldToLocal",
        &osg::computeWorldToLocal,
        "Compute the matrix which transforms objects in world coords to local coords,\n"
        "by accumulating the Transform world to local matrices along the specified node path.\n");

    def("computeLocalToEye",
        &osg::computeLocalToEye,
        "Compute the matrix which transforms objects in local coords to eye coords,\n"
        "by accumulating the Transform local to world matrices along the specified node path \n"
        "and multipling by the supplied initial camera modelview.\n");

    def("computeEyeToLocal",
        &osg::computeEyeToLocal,
        "Compute the matrix which transforms objects in eye coords to local coords,\n"
        "by accumulating the Transform world to local matrices along the specified node path\n"
        "and multipling by the inverse of the supplied initialial camera modelview.\n");

    REGISTER_NODE_CAST(Transform)

    // The Following class is registered as a base python class for the derived classes,
    // so that something like AutoTransform.setReferenceFrame still works
    // 
    {
        TransformClass = new class_Transform("Transform", no_init);

        (*TransformClass)
            .def(init<>())
            .def("setReferenceFrame",
                &osg::Transform::setReferenceFrame,
                "Set the transform's ReferenceFrame, either to be relative to its\n"
                "parent reference frame, or relative to an absolute coordinate\n"
                "frame. RELATIVE_TO_PARENTS is the default.\n"
                "Note: setting the ReferenceFrame to be RELATIVE_TO_ABSOLUTE will\n"
                "also set the CullingActive flag on the transform, and hence all\n"
                "of its parents, to false, thereby disabling culling of it and\n"
                "all its parents.  This is neccessary to prevent inappropriate\n"
                "culling, but may impact cull times if the absolute transform is\n"
                "deep in the scene graph.  It is therefore recommend to only use\n"
                "absolute Transforms at the top of the scene, for such things as\n"
                "headlight LightSources or Heads up displays. \n")
            .def("getReferenceFrame", &osg::Transform::getReferenceFrame)
            .def("computeLocalToWorldMatrix", &osg::Transform::computeLocalToWorldMatrix)
            .def("computeWorldToLocalMatrix", &osg::Transform::computeWorldToLocalMatrix)
            ;

        scope transform_class (*TransformClass);
#       define OSG_ENUM_FRAME(VALUE) frame.value(#VALUE, osg::Transform::VALUE)
        enum_<osg::Transform::ReferenceFrame> frame("ReferenceFrame");
        OSG_ENUM_FRAME(RELATIVE_RF);
        OSG_ENUM_FRAME(ABSOLUTE_RF);
        frame.export_values();
    }

    // The Transform class which can be instantiated from within Python,
    // with the ability to override the methods
    // computeLocalToWorldMatrix and computeWorldToLocalMatrix.
    {
        class_<TransformBase, osg::ref_ptr<TransformBase_imp>, bases<osg::Transform>, boost::noncopyable> transform_base("Transform_base",
            "A Transform is a group node for which all children are transformed by\n"
            "a 4x4 matrix.  It is often used for positioning objects within a scene,\n"
            "producing trackball functionality or for animation.\n"
            "\n"
            "Transform itself does not provide set/get functions, only the interface\n"
            "for defining what the 4x4 transformation is.  Subclasses, such as\n"
            "MatrixTransform and PositionAttitudeTransform support the use of an\n"
            "osg::Matrix or a osg::Vec3/osg::Quat resprectively.\n"
            "The Transform node can be customized via the ComputeTransfromCallback\n"
            "which can be attached to the node.  This might be used to convert from\n"
            "internal representations of the transformation into generic osg::Matrix\n"
            "objects which are used during scene grpah traversal, such as\n"
            "CullTraversal and IntersectionTraversal.\n"
            "\n"
            "Note: if the transformation matrix scales the subgraph then the normals\n"
            "of the underlying geometry will need to be renormalized to be unit\n"
            "vectors once more.  This can be done transparently through OpenGL's \n"
            "use of either GL_NORMALIZE and GL_SCALE_NORMALIZE modes.  For further\n"
            "background reading see the glNormalize documentation in the OpenGL\n"
            "Reference Guide (the blue book). To enable it in the OSG, you simply\n"
            "need to attach a local osg::StateSet to the osg::Transform, and set\n"
            "the appropriate mode to ON via\n"
            "  stateset.setMode(OpenGL.GL.GL_NORMALIZE, osg.StateAttribute.ON)\n",
            no_init);

        transform_base
            .def(init<>())
            .def("computeLocalToWorldMatrix",
                &TransformBase_imp::computeLocalToWorldMatrix_imp)
            .def("computeWorldToLocalMatrix",
                &TransformBase_imp::computeWorldToLocalMatrix_imp)
            ;
    }
}
} // namespace PyOSG
