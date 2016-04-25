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

// TODO Check iterators and support more functionality for iterators!

#include <boost/python.hpp>
#include <boost/ref.hpp>

#include <osg/Vec4>
#include <osg/Image>

#include <string>
#include <iostream>

#include "Image.hpp"
#include "held_ptr.hpp"

using namespace boost::python;

namespace {

// FIXME return the correct image size!
PyObject * getData(osg::Image * self)
{
    return PyString_FromStringAndSize(reinterpret_cast<char *>(self->data()), self->getTotalSizeInBytes());
}

PyObject * getData(osg::Image * self, int column)
{
    return PyString_FromStringAndSize(reinterpret_cast<char *>(self->data(column)), self->getImageSizeInBytes());
}

PyObject * getData(osg::Image * self, int column, int row)
{
    return PyString_FromStringAndSize(reinterpret_cast<char *>(self->data(column, row)), self->getImageSizeInBytes());
}

PyObject * getData(osg::Image * self, int column, int row, int image)
{
    return PyString_FromStringAndSize(reinterpret_cast<char *>(self->data(column, row, image)), self->getImageSizeInBytes());
}

osg::Vec4 * vec4begin(osg::Image& self)
{
    if (self.getDataType() != GL_FLOAT) {
        PyErr_SetString(PyExc_ValueError, "data type isn't float");
        throw_error_already_set();
        return NULL;
    }
    return (osg::Vec4*) self.data();
}
osg::Vec4 * vec4end(osg::Image& self)
{
    int pxls = self.s() * self.t() * self.r();
    return ((osg::Vec4*) self.data()) + pxls;
}
void allocateImage(osg::Image& self, int s,int t,int r, GLenum format,GLenum type)
{
    self.allocateImage(s, t, r, format, type);
}

void setPixel_vec4(osg::Image& self, int col, int row, int img, osg::Vec4& pixel)
{
    unsigned char * data = self.data(col, row, img);
    *data++ = (unsigned char) (pixel[0] * 255.0);
    *data++ = (unsigned char) (pixel[1] * 255.0);
    *data++ = (unsigned char) (pixel[2] * 255.0);
    *data++ = (unsigned char) (pixel[3] * 255.0);
}

void setPixel_tuple(osg::Image& self, int col, int row, int img, tuple& pixel)
{
    unsigned char * data = self.data(col, row, img);

    float r = 0, g = 0, b = 0, a = 1;

    // Fall through intentionally!
    switch (len(pixel)) {
        case 4: a = extract<float>(pixel[3]);
        case 3: b = extract<float>(pixel[2]);
        case 2: g = extract<float>(pixel[1]);
        case 1: r = extract<float>(pixel[0]);
    }
    *data++ = (unsigned char) (r * 255.0);
    *data++ = (unsigned char) (g * 255.0);
    *data++ = (unsigned char) (b * 255.0);
    *data++ = (unsigned char) (a * 255.0);
}
} // namespace

namespace PyOSG {

class_Image * ImageClass = NULL;

void init_Image()
{
    ImageClass = new class_Image("Image", no_init);

    (*ImageClass)
        .def(init<>())
        .def("setFileName",
            &osg::Image::setFileName)
        .def("getFileName",
            &osg::Image::getFileName,
            return_value_policy<copy_const_reference>())

        .def("allocateImage",
            &osg::Image::allocateImage,
           "allocated a pixel block of specified size and type.")

        .def("allocateImage",
            &allocateImage)

        .def("setImage",
            &osg::Image::setImage,
            "set the image data and format."
            "note, when the packing value is negative (the default is -1) this method assumes"
            "a _packing width of 1 if the width is not a multiple of 4,"
            "otherwise automatically sets to _packing to 4. If a positive"
            "value of packing is supplied than _packing is simply set to that value.")

        .def("readPixels",
            &osg::Image::readPixels,
            "readPixels from screen at specified position and size, using glReadPixels.\n"
            "Create memory for storage if required, reuse existing pixel coords if possible.\n"
            "if pixelFormat or dataType*/\n")

        .def("readImageFromCurrentTexture",
            &osg::Image::readImageFromCurrentTexture,
            "read the contents of the current bound texture, handling compressed formats if present.\n"
            "Create memory for storage if required, reuse existing pixel coords if possible.\n")

        .def("scaleImage",
            (void (osg::Image::*)(int, int, int)) &osg::Image::scaleImage,
            "Scale image to specified size.")

        .def("scaleImage",
            (void (osg::Image::*)(int, int, int, GLenum)) &osg::Image::scaleImage,
            "Scale image to specified size.")

        .def("copySubImage",
            &osg::Image::copySubImage,
            "Copy a source Image into a subpart of this Image at specified position."
            "Typically used to copy to an already allocated image, such as creating"
            "a 3D image from a stack 2D images."
            "If the this Image is empty then image data is created to"
            "accomodate the imaging image in its offset position."
            "If source is NULL then no operation happens, this Image is left unchanged.")

        .def("s", &osg::Image::s)
        .def("t", &osg::Image::t)
        .def("r", &osg::Image::r)


        .def("setPixelFormat", &osg::Image::setPixelFormat)
        .def("getPixelFormat", &osg::Image::getPixelFormat)

        .def("setInternalTextureFormat", &osg::Image::setInternalTextureFormat)
        .def("getInternalTextureFormat", &osg::Image::getInternalTextureFormat)

        .def("getDataType", &osg::Image::getDataType)
        .def("getPacking", &osg::Image::getPacking)
        .def("getPixelSizeInBits", &osg::Image::getPixelSizeInBits)

        .def("getRowSizeInBytes", &osg::Image::getRowSizeInBytes)
        .def("getImageSizeInBytes", &osg::Image::getImageSizeInBytes)
        .def("getTotalSizeInBytes", &osg::Image::getTotalSizeInBytes)
        .def("getTotalSizeInBytesIncludingMipmaps", &osg::Image::getTotalSizeInBytesIncludingMipmaps)

        .def("data", (PyObject * (*)(osg::Image *)) &getData)
        .def("data", (PyObject * (*)(osg::Image *, int)) &getData)
        .def("data", (PyObject * (*)(osg::Image *, int, int)) &getData)
        .def("data", (PyObject * (*)(osg::Image *, int, int, int)) &getData)

        .def("flipHorizontal", &osg::Image::flipHorizontal)
        .def("flipVertical", &osg::Image::flipVertical)

        .def("ensureValidSizeForTexturing", &osg::Image::ensureValidSizeForTexturing)
        .def("dirty", &osg::Image::dirty)
        .def("setModifiedCount", &osg::Image::setModifiedCount)
        .def("getModifiedCount", &osg::Image::getModifiedCount)

        .def("isPackedType", &osg::Image::isPackedType)
        /*** TODO
        static unsigned int computeNumComponents(GLenum pixelFormat);
        static unsigned int computePixelSizeInBits(GLenum pixelFormat,GLenum type);
        static unsigned int computeRowWidthInBytes(int width,GLenum pixelFormat,GLenum type,int packing);
        static int computeNearestPowerOfTwo(int s,float bias=0.5f);
        ***/

        .def("isMipmap", &osg::Image::isMipmap)
        .def("getNumMipmapLevels", &osg::Image::getNumMipmapLevels)
        .def("setMipmapLevels", &osg::Image::setMipmapLevels)
        // TODO image.def("getMipmapData", &osg::Image::getMipmapData)
        // .def("computeMipMaps", &osg::Image::computeMipMaps)
        .def("isImageTranslucent", &osg::Image::isImageTranslucent)

        .add_property("dataAsVec4", range<return_value_policy<reference_existing_object> >(&vec4begin, &vec4end))
        .def("setPixel", &setPixel_vec4)
        .def("setPixel", &setPixel_tuple)
        ;
}
} // namespace
