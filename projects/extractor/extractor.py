#!/usr/bin/env python
import extractor
from extractor import Keypoint
import numpy as np

kps = [Keypoint(1.0, 2.0, 3.0),
        Keypoint(4.0, 5.0, 6.0),
        Keypoint(7.0, 8.0, 9.0)]

output = extractor.extract(kps)

print "Output: %s" %(str(output))

print ""

for kp in kps:
    print kp




