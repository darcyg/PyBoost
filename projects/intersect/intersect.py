#!/usr/bin/env python
import intersect
from intersect import Keypoint, Image, Detector
import numpy as np

#kps = [Keypoint(1.0, 2.0, 3.0),
        #Keypoint(4.0, 5.0, 6.0),
        #Keypoint(7.0, 8.0, 9.0)]

# construct image
data = np.array([10, 20, 30, 40, 50, 60], dtype=float)
image = Image(3, 2, data)
#image = Image(3, 2)

# detect keypoints
keypoints = Detector.detect(image)

for kp in keypoints:
    print kp




