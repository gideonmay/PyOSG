#!/usr/bin/env python
from PyOSG import osgDB
from PyOSG import osgGA
from PyOSG import osgViewer

def main():
    # construct the viewer.
    viewer = osgViewer.Viewer()

    # read the scene from the list of file specified commandline args.
    loadedModel = osgDB.readNodeFiles(["cow.osg"])

    if not loadedModel:
        print ("No data loaded")
        return 1

    viewer.setSceneData(loadedModel)

    viewer.setCameraManipulator(osgGA.TrackballManipulator())

    viewer.setUpViewInWindow(100,100,400,400, 0)

    viewer.realize()
    # viewer.run()

    # osr = xyzUtil.OffScreenRenderer(200,200)
    # osr.scene(loadedModel)

    wtf = osgViewer.WriteToFile("image", "png")

    sch = osgViewer.ScreenCaptureHandler()
    sch.setCaptureOperation(wtf)

    bs = loadedModel.getBound()
    print ("Bounding sphere = ", bs)

    simtime = 0.0
    while not viewer.done():
        # print(simtime)
        viewer.frame(simtime)
        # sch.captureNextFrame(viewer)

        # osr.render()
        # osr.writeImageFile(("dump%f.png" % simtime))
        simtime += 0.001

if __name__=="__main__":
    main()
