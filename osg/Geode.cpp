#include <boost/python/class.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/ref.hpp>

#include <osg/Geode>

#include <string>
#include <iostream>

#include "Node.hpp"
#include "Geode.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {

DEFINE_NODE_CAST(Geode)

#if 0
class BoostObject : public osg::Referenced {
    public:
        inline BoostObject(object* obj):Referenced(),_object(obj) {}
        BoostObject(const BoostObject& obj): Referenced(), _object(obj._object) {}
        
        object*    obj() {return _object; }
    protected:
        ~BoostObject() {}

    private:

        object*     _object;
};

bool addDrawable(osg::Geode * self, object& obj)
{
    osg::Drawable * drawable = extract<osg::Drawable *>(obj);
    osg::ref_ptr<BoostObject> o = new BoostObject(&obj);

    drawable->setUserData(o.get());

    std::cerr << "Geode.addDrawable:" << self << "," << drawable << ", object: " << std::endl;
    return self->addDrawable(drawable);
}

object* getDrawable(osg::Geode * self, unsigned int i )
// osg::Drawable* getDrawable(osg::Geode * self, unsigned int i )
{
    osg::Drawable * drawable = self->getDrawable(i);
    BoostObject* o = dynamic_cast<BoostObject *>(drawable->getUserData());

    std::cerr << "Geode.getDrawable:" << self << "," << i << "," << drawable << ", object = " << std::endl;
    return o->obj();
}
#endif
} // namespace


namespace PyOSG {

class_Geode * GeodeClass = NULL;

void init_Geode()
{
    REGISTER_NODE_CAST(Geode)

    GeodeClass = new class_Geode("Geode",
        "Leaf Node for grouping Drawables.",
        no_init);

    (*GeodeClass)
        .def(init<>())

        .def("addDrawable", 
            &osg::Geode::addDrawable,
            "Add Drawable to Geode.\n"
            "If drawable is not None and is not contained in Geode then increment its  \n"
            "reference count, add it to the drawables list and dirty the bounding \n"
            "sphere to force it to recompute on next getBound() and return true for success.\n"
            "Otherwise return false.\n")

        .def("removeDrawable",
            (bool (osg::Geode::*)(osg::Drawable *)) 
            &osg::Geode::removeDrawable)

        .def("removeDrawable",
            (bool (osg::Geode::*)(unsigned int, unsigned int)) 
            &osg::Geode::removeDrawable)

        .def("replaceDrawable", 
            &osg::Geode::replaceDrawable,
            "Replace specified Drawable with another Drawable.\n"
            "Decrement the reference count origGSet and increments the\n"
            "reference count of newGset, and dirty the bounding sphere\n"
            "to force it to recompute on next getBound() and returns true.\n"
            "If origDrawable is not found then return false and do not \n"
            "add newGset.  If newGset is NULL then return false and do\n"
            "not remove origGset.\n")

        .def("setDrawable", 
            &osg::Geode::setDrawable)

        .def("getNumDrawables", 
            &osg::Geode::getNumDrawables,
            "return the number of drawable's.\n")

        .def("getDrawable", 
            (osg::Drawable*(osg::Geode::*)(unsigned int))
            &osg::Geode::getDrawable, 
            return_value_policy<manage_osg_object>(),
            "return drawable at position i.")

        .def("containsDrawable", 
            &osg::Geode::containsDrawable,
            "return true if drawable is contained within Geode.")

        .def("getDrawableIndex", 
            &osg::Geode::getDrawableIndex)

        .def("compileDrawables", 
            &osg::Geode::compileDrawables,
            "compile OpenGL Display List for each drawable")

        /** return the Geode's bounding box, which is the union of all the
          * bounding boxes of the geode's drawables.*/
        .def("getBoundingBox",
            &osg::Geode::getBoundingBox,
            return_value_policy<copy_const_reference>())
        ;
}
}
