#!/usr/bin/env python

# Copyright (C) 2002-2003 Gideon May (gideon@computer.org)
#
# Permission to copy, use, sell and distribute this software is granted
# provided this copyright notice appears in all copies.
# Permission to modify the code and to distribute modified code is granted
# provided this copyright notice appears in all copies, and a notice
# that the code was modified is included with the copyright notice.
#
# This software is provided "as is" without express or implied warranty,
# and with no claim as to its suitability for any purpose.

# -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2003 Robert Osfield 
#
# This application is open source and may be redistributed and/or modified   
# freely and without restriction, both in commericial and non commericial applications,
# as long as this copyright notice is maintained.
# 
# This application is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

from PyOSG import Producer
from PyOSG import osg
from PyOSG import osgGA
from PyOSG import osgDB
from PyOSG import osgUtil
from PyOSG import osgProducer
from PyOSG import osgText
import sys
import math

def main(argv):
    # use an ArgumentParser object to manage the program arguments.
    arguments =  osg.ArgumentParser(argv)
    
    # set up the usage document, in case we need to print out how to use this program.
    arguments.getApplicationUsage().setApplicationName(arguments.getApplicationName())
    arguments.getApplicationUsage().setDescription(arguments.getApplicationName()+" is the standard OpenSceneGraph example which loads and visualises 3d models.")
    arguments.getApplicationUsage().setCommandLineUsage(arguments.getApplicationName()+" [options] filename ...")
    arguments.getApplicationUsage().addCommandLineOption("-h or --help","Display this information")

    au = arguments.getApplicationUsage()
#    print sys.stderr
#    f = open("c:/tmp/x")
#    au.write_out(f)
#    au.write_out(sys.stderr)
#    return
    

    # construct the viewer.
    viewer = osgProducer.Viewer(arguments)

    # set up the value with sensible default event handlers.
    viewer.setUpViewer(osgProducer.Viewer.STANDARD_SETTINGS)

    # get details on keyboard and mouse bindings used by the viewer.
    viewer.getUsage(arguments.getApplicationUsage())

    # if user request help write it out to cout.
    if arguments.read("-h") or arguments.read("--help"):
        arguments.getApplicationUsage().write()
        return 1

    # any option left unread are converted into errors to write out later.
    arguments.reportRemainingOptionsAsUnrecognized()

    # report any errors if they have occured when parsing the program aguments.
    if arguments.errors():
        arguments.writeErrorMessages()
        return 1
    
    if arguments.argc()<=1:
        arguments.getApplicationUsage().write(osg.ApplicationUsage.COMMAND_LINE_OPTION)
        return 1

    # read the scene from the list of file specified commandline args.
    loadedModel = osgDB.readNodeFiles(arguments)

    # if no model has been successfully loaded report failure.
    if not loadedModel: 
        print arguments.getApplicationName(), " No data loaded"
        return 1

    # optimize the scene graph, remove rendundent nodes and state etc.
    optimizer =  osgUtil.Optimizer()
    optimizer.optimize(loadedModel)

    # set the scene to render
    viewer.setSceneData(loadedModel)

    # create the windows and run the threads.
    viewer.realize()

    while not viewer.done():
        # wait for all cull and draw threads to complete.
        viewer.sync()

        # update the scene by traversing it with the the update visitor which will
        # call all node update callbacks and animations.
        viewer.update()
         
        # fire off the cull and draw traversals of the scene.
        viewer.frame()
    
    # wait for all cull and draw threads to complete before exit.
    viewer.sync()

    return 0


main(sys.argv)
