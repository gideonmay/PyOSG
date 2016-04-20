#include <boost/python.hpp>

#include <osgGA/GUIEventAdapter>

#include "held_ptr.hpp"

using namespace boost::python;

namespace {
int osgGAGUIEventAdapter_getEventType(osgGA::GUIEventAdapter * self)
{
    return int(self->getEventType());
}

class GUIEventAdapterBase : public osgGA::GUIEventAdapter {
  public:
    GUIEventAdapterBase() : osgGA::GUIEventAdapter() {}
};

class GUIEventAdapterBase_imp : public GUIEventAdapterBase {
  public:
    GUIEventAdapterBase_imp(PyObject * p) : _self(p) {
        Py_XINCREF(_self);
    }

    virtual ~GUIEventAdapterBase_imp() {
        Py_XDECREF(_self);
    }

    /** Get the EventType of the GUI event.*/
    virtual osgGA::GUIEventAdapter::EventType getEventType() const
    {
        osgGA::GUIEventAdapter::EventType event = osgGA::GUIEventAdapter::NONE;
        try {
            event = call_method<osgGA::GUIEventAdapter::EventType>(_self, "getEventType");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return event;
    }

    /** key pressed, return -1 if inappropriate for this event. */
    virtual int getKey() const {
        int key = -1;
        try {
            key =  call_method<int>(_self, "getKey");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return key;
    }

    /** button pressed/released, return -1 if inappropriate for this event.*/
    virtual int getButton() const {
        int button = -1;
        try {
            button =  call_method<int>(_self, "getButton");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return button;
    }


    /** manimum x mouse position. */
    virtual float getXmin() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getXmin");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** maximum x mouse position. */
    virtual float getXmax() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getXmax");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** minimum y mouse position. */
    virtual float getYmin() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getYmin");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** maximum y mouse position. */   
    virtual float getYmax() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getYmax");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** current mouse x position.*/
    virtual float getX() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getX");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** current mouse y position.*/
    virtual float getY() const {
        float val = 0;
        try {
            val =  call_method<float>(_self, "getY");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** current mouse button state */
    virtual unsigned int getButtonMask() const {
        unsigned int val = 0;
        try {
            val =  call_method<unsigned int>(_self, "getButtonMask");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** current modkey state */
    virtual unsigned int getModKeyMask() const {
        unsigned int val = 0;
        try {
            val =  call_method<unsigned int>(_self, "getModKeyMask");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

    /** time in seconds of event. */
    virtual double time() const {
        double val = 0;
        try {
            val =  call_method<double>(_self, "time");
        } catch(...) {
            handle_exception();
            PyErr_Print();
            throw_error_already_set();
        }
        return val;
    }

  private:
    PyObject * _self;
};
} // namespace

namespace PyOSG {
void init_GUIEventAdapter()
{
    class_<osgGA::GUIEventAdapter, osg::ref_ptr<osgGA::GUIEventAdapter>, bases<osg::Referenced>, boost::noncopyable> event_adapter("GUIEventAdapter", no_init);

    {
        scope event_adapter_scope(event_adapter);

        event_adapter
            .def("getEventType",
                    // &osgGAGUIEventAdapter_getEventType)
                    &osgGA::GUIEventAdapter::getEventType)
            .def("getKey",
                    &osgGA::GUIEventAdapter::getKey)
            .def("getButton",
                    &osgGA::GUIEventAdapter::getButton)
            .def("setMouseYOrientation",
                    &osgGA::GUIEventAdapter::setMouseYOrientation)
            .def("getMouseYOrientation",
                    &osgGA::GUIEventAdapter::getMouseYOrientation)
            .def("getXmin",
                    &osgGA::GUIEventAdapter::getXmin)
            .def("getXmax",
                    &osgGA::GUIEventAdapter::getXmax)
            .def("getYmin",
                    &osgGA::GUIEventAdapter::getYmin)
            .def("getYmax",
                    &osgGA::GUIEventAdapter::getYmax)
            .def("getX",
                    &osgGA::GUIEventAdapter::getX)
            .def("getY",
                    &osgGA::GUIEventAdapter::getY)
            .def("getButtonMask",
                    &osgGA::GUIEventAdapter::getButtonMask)
            .def("getModKeyMask",
                    &osgGA::GUIEventAdapter::getModKeyMask)
            .def("time",
                    &osgGA::GUIEventAdapter::time)
            .def("getXnormalized",
                    &osgGA::GUIEventAdapter::getXnormalized)
            /** return the getX() value normalised to the range of -1 to 1.
              * -1 would be the left hand side of the window.
              * 0.0 would be the middle of the window.
              * +1 would be the right hand side of the window.*/

            .def("getYnormalized",
                    &osgGA::GUIEventAdapter::getYnormalized)
            /** return the getY() value normalised to the range of -1 to 1.
              * -1 would be the bottom of the window.
              * 0.0 would be the middle of the window.
              * +1 would be the top of the window.*/
            ;

#   define BUTTON_MASK(VALUE) button_mask.value(#VALUE, osgGA::GUIEventAdapter::VALUE)
            enum_<osgGA::GUIEventAdapter::MouseButtonMask> button_mask("MouseButtonMask");
            BUTTON_MASK(LEFT_MOUSE_BUTTON);
            BUTTON_MASK(MIDDLE_MOUSE_BUTTON);
            BUTTON_MASK(RIGHT_MOUSE_BUTTON);
            button_mask.export_values();

#   define EVENT_TYPE(VALUE) event_type.value(#VALUE, osgGA::GUIEventAdapter::VALUE)
            enum_<osgGA::GUIEventAdapter::EventType> event_type("EventType");
            EVENT_TYPE(PUSH);
            EVENT_TYPE(RELEASE);
            EVENT_TYPE(DOUBLECLICK);
            EVENT_TYPE(DRAG);
            EVENT_TYPE(MOVE);
            EVENT_TYPE(KEYDOWN);
            EVENT_TYPE(KEYUP);
            EVENT_TYPE(FRAME);
            EVENT_TYPE(RESIZE);
            EVENT_TYPE(NONE);
            event_type.export_values();

#   define KEY_SYMBOL(VALUE) key_symbol.value(#VALUE, osgGA::GUIEventAdapter::VALUE)
            enum_<osgGA::GUIEventAdapter::KeySymbol> key_symbol("KeySymbol");
            KEY_SYMBOL(KEY_Space);
            KEY_SYMBOL(KEY_BackSpace);
            KEY_SYMBOL(KEY_Tab);
            KEY_SYMBOL(KEY_Linefeed);
            KEY_SYMBOL(KEY_Clear);
            KEY_SYMBOL(KEY_Return);
            KEY_SYMBOL(KEY_Pause);
            KEY_SYMBOL(KEY_Scroll_Lock);
            KEY_SYMBOL(KEY_Sys_Req);
            KEY_SYMBOL(KEY_Escape);
            KEY_SYMBOL(KEY_Delete);
            KEY_SYMBOL(KEY_Home);
            KEY_SYMBOL(KEY_Left);
            KEY_SYMBOL(KEY_Up);
            KEY_SYMBOL(KEY_Right);
            KEY_SYMBOL(KEY_Down);
            KEY_SYMBOL(KEY_Prior);
            KEY_SYMBOL(KEY_Page_Up);
            KEY_SYMBOL(KEY_Next);
            KEY_SYMBOL(KEY_Page_Down);
            KEY_SYMBOL(KEY_End);
            KEY_SYMBOL(KEY_Begin);
            KEY_SYMBOL(KEY_Select);
            KEY_SYMBOL(KEY_Print);
            KEY_SYMBOL(KEY_Execute);
            KEY_SYMBOL(KEY_Insert);
            KEY_SYMBOL(KEY_Undo);
            KEY_SYMBOL(KEY_Redo);
            KEY_SYMBOL(KEY_Menu);
            KEY_SYMBOL(KEY_Find);
            KEY_SYMBOL(KEY_Cancel);
            KEY_SYMBOL(KEY_Help);
            KEY_SYMBOL(KEY_Break);
            KEY_SYMBOL(KEY_Mode_switch);
            KEY_SYMBOL(KEY_Script_switch);
            KEY_SYMBOL(KEY_Num_Lock);
            KEY_SYMBOL(KEY_KP_Space);
            KEY_SYMBOL(KEY_KP_Tab);
            KEY_SYMBOL(KEY_KP_Enter);
            KEY_SYMBOL(KEY_KP_F1);
            KEY_SYMBOL(KEY_KP_F2);
            KEY_SYMBOL(KEY_KP_F3);
            KEY_SYMBOL(KEY_KP_F4);
            KEY_SYMBOL(KEY_KP_Home);
            KEY_SYMBOL(KEY_KP_Left);
            KEY_SYMBOL(KEY_KP_Up);
            KEY_SYMBOL(KEY_KP_Right);
            KEY_SYMBOL(KEY_KP_Down);
            KEY_SYMBOL(KEY_KP_Prior);
            KEY_SYMBOL(KEY_KP_Page_Up);
            KEY_SYMBOL(KEY_KP_Next);
            KEY_SYMBOL(KEY_KP_Page_Down);
            KEY_SYMBOL(KEY_KP_End);
            KEY_SYMBOL(KEY_KP_Begin);
            KEY_SYMBOL(KEY_KP_Insert);
            KEY_SYMBOL(KEY_KP_Delete);
            KEY_SYMBOL(KEY_KP_Equal);
            KEY_SYMBOL(KEY_KP_Multiply);
            KEY_SYMBOL(KEY_KP_Add);
            KEY_SYMBOL(KEY_KP_Separator);
            KEY_SYMBOL(KEY_KP_Subtract);
            KEY_SYMBOL(KEY_KP_Decimal);
            KEY_SYMBOL(KEY_KP_Divide);
            KEY_SYMBOL(KEY_KP_0);
            KEY_SYMBOL(KEY_KP_1);
            KEY_SYMBOL(KEY_KP_2);
            KEY_SYMBOL(KEY_KP_3);
            KEY_SYMBOL(KEY_KP_4);
            KEY_SYMBOL(KEY_KP_5);
            KEY_SYMBOL(KEY_KP_6);
            KEY_SYMBOL(KEY_KP_7);
            KEY_SYMBOL(KEY_KP_8);
            KEY_SYMBOL(KEY_KP_9);
            KEY_SYMBOL(KEY_F1);
            KEY_SYMBOL(KEY_F2);
            KEY_SYMBOL(KEY_F3);
            KEY_SYMBOL(KEY_F4);
            KEY_SYMBOL(KEY_F5);
            KEY_SYMBOL(KEY_F6);
            KEY_SYMBOL(KEY_F7);
            KEY_SYMBOL(KEY_F8);
            KEY_SYMBOL(KEY_F9);
            KEY_SYMBOL(KEY_F10);
            KEY_SYMBOL(KEY_F11);
            KEY_SYMBOL(KEY_F12);
            KEY_SYMBOL(KEY_F13);
            KEY_SYMBOL(KEY_F14);
            KEY_SYMBOL(KEY_F15);
            KEY_SYMBOL(KEY_F16);
            KEY_SYMBOL(KEY_F17);
            KEY_SYMBOL(KEY_F18);
            KEY_SYMBOL(KEY_F19);
            KEY_SYMBOL(KEY_F20);
            KEY_SYMBOL(KEY_F21);
            KEY_SYMBOL(KEY_F22);
            KEY_SYMBOL(KEY_F23);
            KEY_SYMBOL(KEY_F24);
            KEY_SYMBOL(KEY_F25);
            KEY_SYMBOL(KEY_F26);
            KEY_SYMBOL(KEY_F27);
            KEY_SYMBOL(KEY_F28);
            KEY_SYMBOL(KEY_F29);
            KEY_SYMBOL(KEY_F30);
            KEY_SYMBOL(KEY_F31);
            KEY_SYMBOL(KEY_F32);
            KEY_SYMBOL(KEY_F33);
            KEY_SYMBOL(KEY_F34);
            KEY_SYMBOL(KEY_F35);
            KEY_SYMBOL(KEY_Shift_L);
            KEY_SYMBOL(KEY_Shift_R);
            KEY_SYMBOL(KEY_Control_L);
            KEY_SYMBOL(KEY_Control_R);
            KEY_SYMBOL(KEY_Caps_Lock);
            KEY_SYMBOL(KEY_Shift_Lock);
            KEY_SYMBOL(KEY_Meta_L);
            KEY_SYMBOL(KEY_Meta_R);
            KEY_SYMBOL(KEY_Alt_L);
            KEY_SYMBOL(KEY_Alt_R);
            KEY_SYMBOL(KEY_Super_L);
            KEY_SYMBOL(KEY_Super_R);
            KEY_SYMBOL(KEY_Hyper_L);
            KEY_SYMBOL(KEY_Hyper_R);
            key_symbol.export_values();

#   define MOD_KEY_MASK(VALUE) mod_key_mask.value(#VALUE, osgGA::GUIEventAdapter::VALUE)
            enum_<osgGA::GUIEventAdapter::ModKeyMask> mod_key_mask("ModKeyMask");
            MOD_KEY_MASK(MODKEY_LEFT_SHIFT);
            MOD_KEY_MASK(MODKEY_RIGHT_SHIFT);
            MOD_KEY_MASK(MODKEY_LEFT_CTRL);
            MOD_KEY_MASK(MODKEY_RIGHT_CTRL);
            MOD_KEY_MASK(MODKEY_LEFT_ALT);
            MOD_KEY_MASK(MODKEY_RIGHT_ALT);
            MOD_KEY_MASK(MODKEY_LEFT_META);
            MOD_KEY_MASK(MODKEY_RIGHT_META);
            MOD_KEY_MASK(MODKEY_NUM_LOCK);
            MOD_KEY_MASK(MODKEY_CAPS_LOCK);
            MOD_KEY_MASK(MODKEY_CTRL);
            MOD_KEY_MASK(MODKEY_SHIFT);
            MOD_KEY_MASK(MODKEY_ALT);
            MOD_KEY_MASK(MODKEY_META);
            mod_key_mask.export_values();

#   define MOUSE_Y_ORIENTATION(VALUE) mouse_y_orientation.value(#VALUE, osgGA::GUIEventAdapter::VALUE)
            enum_<osgGA::GUIEventAdapter::MouseYOrientation> mouse_y_orientation("MouseYOrientation");
            MOUSE_Y_ORIENTATION(Y_INCREASING_UPWARDS);
            MOUSE_Y_ORIENTATION(Y_INCREASING_DOWNWARDS);
            mouse_y_orientation.export_values();
        }

    class_<GUIEventAdapterBase, osg::ref_ptr<GUIEventAdapterBase_imp>, bases<osgGA::GUIEventAdapter>, boost::noncopyable> ea_base("GUIEventAdapter_base",
        "Pure virtual base class for adapting platform specific events into\n"
        "generic keyboard and mouse events. \n"
        "\n"
        "Used as GUI toolkit-independent input into GUIEventAdapters. Viewer\n"
        "writers should subclass this base class to implement the functionality\n"
        "to translate one of their GUI events, e.g. a Qt Event or an MFC Event,\n"
        "as appropriate.\n",
        no_init);
    ea_base
        .def(init<>())
        ;
}
}

