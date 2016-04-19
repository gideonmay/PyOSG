import _osgGA

__all__ = dir(_osgGA)
__ignore = ['__file__', '__module__', '__name__']

for (key, val) in _osgGA.__dict__.items():
    if key in __ignore: continue
    globals()[key] = val

