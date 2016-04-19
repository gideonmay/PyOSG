# Copyriht (C) 2002-2003 Gideon May (gideon@computer.org)
#
# Permission to copy, use, sell and distribute this software is granted
# provided this copyright notice appears in all copies.
# Permission to modify the code and to distribute modified code is granted
# provided this copyright notice appears in all copies, and a notice
# that the code was modified is included with the copyright notice.
#
# This software is provided "as is" without express or implied warranty,
# and with no claim as to its suitability for any purpose.

"""PyOSG  is package which allows to write high performance
3D graphics programs in python. It's build on top of 
OpenSceneGraph, a scene graph library using OpenGL.
The glue is boost_python, an excellent library for 
writing wrapper libraries.
"""

import os

# __all__ = ['Producer', 'osg', 'osgUtil', 'osgGA', 'osgDB', 'osgProducer', 'osgParticle', 'osgText', 'osgSim', 'osgFX']
# __all__ = ['osg', 'osgUtil', 'osgGA', 'osgDB', 'osgParticle', 'osgText', 'osgSim', 'osgFX', 'osgViewer']
__all__ = ['osg', 'osgUtil', 'osgGA', 'osgDB', 'osgViewer']

version_info = (1,0,0)
build_info = 1
__version__ = "%d.%d.%d" % version_info

