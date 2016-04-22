import _osg
import _osgDB

__all__ = dir(_osgDB)
__ignore = ['__file__', '__module__', '__name__']

for (key, val) in _osgDB.__dict__.items():
    if key in __ignore: continue
    globals()[key] = val


