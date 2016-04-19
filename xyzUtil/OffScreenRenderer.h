
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

#ifndef __OSG_TOOLS_OFF_SCREEN_RENDERER_H__
#define __OSG_TOOLS_OFF_SCREEN_RENDERER_H__

#include <osg/ref_ptr>
#include <osg/Image>
#include <osg/Matrixd>

namespace OsgTools {


typedef osg::ref_ptr<osg::Image> ImagePtr;

class OffScreenRenderer
{
public:

  // Set the scene.
  virtual void   scene ( osg::Node* ) = 0;

  // Render.
  virtual ImagePtr render() const = 0;

  // Set the view matrix.
  virtual void viewMatrix ( const osg::Matrixd& matrix ) = 0;

protected:
  
  OffScreenRenderer();
  virtual ~OffScreenRenderer();

private:

};


}

#endif // __OSG_TOOLS_OFF_SCREEN_RENDERER_H__
