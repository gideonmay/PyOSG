# Python bindings for OpenSceneGraph

Compile OpenSceneGraph 3.4.0
for OSX :
set the following cmake variable :
CMAKE_INSTALL_NAME_DIR to /opt/local/lib (or /usr/local/lib)
CMAKE_INSTALL_PREFIX to /opt/local (or /usr/local)
this sets the correct full path of all the shared libraries - otool.