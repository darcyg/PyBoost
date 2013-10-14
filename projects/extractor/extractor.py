#!/usr/bin/env python
import extractor
from extractor import Keypoint
import numpy as np

"""
This is extractor file, it creates a keypoint
"""

kps = [Keypoint(1.0, 2.0, 3.0),
        Keypoint(4.0, 5.0, 6.0),
        Keypoint(7.0, 8.0, 9.0)]

output = extractor.extract(kps)

print "Output: %s" %(str(output))

print ""

def do():
    """
    this function does stuff
    """
    for kp in kps:
        print kp

do()




