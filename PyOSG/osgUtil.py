import _osg
import _osgUtil

__all__ = dir(_osgUtil)
__ignore = ['__file__', '__module__', '__name__']

for (key, val) in _osgUtil.__dict__.items():
    if key in __ignore: continue
    globals()[key] = val

