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

from PyOSG import osg

def main():
    print ("OpenSceneGraph version : " + osg.GetVersion())
    print ("PyOSG Version: " + osg.__version__)

if __name__ == "__main__":
    main()
