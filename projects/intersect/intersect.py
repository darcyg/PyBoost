#!/usr/bin/env python
import intersect
from intersect import Keypoint, Image, Detector, Extractor
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
keypoints = detector.keypoints

# get features from keypoints
extractor = Extractor()
extractor.extract(keypoints)

features = extractor.getFeatures()

extractor.fuckWithFeatures()

print ""

print "Python:"
print "------------------------------------"
print features

#for kp in keypoints:
    #print kp

