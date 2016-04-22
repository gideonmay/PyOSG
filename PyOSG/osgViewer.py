import _osg
import _osgViewer

__all__ = dir(_osgViewer)
__ignore = ['__file__', '__module__', '__name__']

for (key, val) in _osgViewer.__dict__.items():
    if key in __ignore: continue
    globals()[key] = val

