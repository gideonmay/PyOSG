
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2008, Adam Kubach
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class to render to off screen target, without needed a window.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OSG_TOOLS_OFF_SCREEN_RENDERER_P_BUFFER_H__
#define __OSG_TOOLS_OFF_SCREEN_RENDERER_P_BUFFER_H__

#include "OffScreenRenderer.h"

#include <osg/Matrixd>

#include <osg/ref_ptr>
#include <osgViewer/Viewer>

namespace OsgTools {
    
typedef osg::ref_ptr<osg::Image> ImagePtr;

class OffScreenRendererPBuffer : public OffScreenRenderer
{
public:
  OffScreenRendererPBuffer ( unsigned int width, unsigned int height );

  // Set the scene.
  virtual void           scene ( osg::Node* );

  // Render.
  virtual ImagePtr       render() const;

  // Set the view matrix.
  virtual void           viewMatrix ( const osg::Matrixd& matrix );

  virtual bool            writeImageFile(const std::string& filename);

//protected:
  
  virtual ~OffScreenRendererPBuffer();

private:

  // Initialize.
  void           _init ( unsigned int width, unsigned int height );

  osg::ref_ptr<osgViewer::Viewer> _viewer;
  osg::ref_ptr<osg::Image> _image;
};
}


#endif // __OSG_TOOLS_OFF_SCREEN_RENDERER_P_BUFFER_H__
