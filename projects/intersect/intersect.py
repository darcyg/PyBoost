#!/usr/bin/env python
import intersect
from intersect import Keypoint, Image, Detector
import numpy as np

#kps = [Keypoint(1.0, 2.0, 3.0),
        #Keypoint(4.0, 5.0, 6.0),
        #Keypoint(7.0, 8.0, 9.0)]

# construct image
data = np.array([10, 20, 30, 40, 50, 60], dtype=np.uint8)
image = Image(3, 2, data)
image.fuck()

#image = Image(3, 2)
# keypoints[2] = Keypoint(1000,2000,3000)

# detect keypoints
detector = Detector()

detector.detect(image)
keypoints = detector.keypoints
    
filename = "keypoints.bin"
#detector.saveKeypoints(filename)
value = detector.saveKeypoints()

keypoints[2] = Keypoint(1000,2000,3000)

#detector.loadKeypoints(filename)
detector.loadKeypoints(value)

keypoints = detector.keypoints

for kp in keypoints:
    print kp

print data
