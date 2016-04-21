import _osg

__all__ = dir(_osg)
__ignore = ['__file__', '__module__', '__name__', '__doc__']

for (key, val) in _osg.__dict__.items():
    if key in __ignore: continue
    globals()[key] = val
