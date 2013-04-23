#!/usr/bin/env python
import intersect
from intersect import Keypoint, Image, Detector, KeypointVector
import numpy as np
import redis
import time

db = redis.StrictRedis(host='localhost', port=6379, db=0)

# make sure there isn't stale data
db.flushall()

num_keypoints = 1000
keypoints = KeypointVector()

for i in range(num_keypoints):
    k = Keypoint(i ,i+1, i+2)
    keypoints.append(k)

# detect keypoints
detector = Detector()
detector.fake_detect(keypoints)
keypoints = detector.keypoints

# save
value = detector.saveKeypoints()

num_operations = 1000

# time insertion
istime = time.time()
for i in range(num_operations):
    value = detector.saveKeypoints()
    db.set(i, value)
ietime = time.time()
iduration = int((ietime - istime) * 1000)

print "Total Insert Time: %s, (%s ms/set)" %(str(iduration), str(iduration/float(num_operations)))

# time get
stime = time.time()
#for i in range(num_operations):
    #db.get(i)
    #detector.loadKeypoints(value)

keys = range(num_operations)
values = db.mget(keys)
stime = time.time()
for value in values:
    detector.loadKeypoints(value)
etime = time.time()
duration = int((etime - stime) * 1000)

#print "Total Get Time: %s, (%s ms/get)" %(str(duration), str(duration/float(num_operations)))
print "Total Get Time: %s, (%s ms/get)" %(str(duration), str(duration))

print "----------------------------------------\n"

# construct image
data = np.array([10, 20, 30, 40, 0, 60], dtype=np.uint8)
image = Image(3, 2, data)

# save data to redis
image.saveToRedis("image_key")
value = db.get("image_key")

#array = np.array(range(1000), dtype=np.uint8)
#string = array.tostring()
#db.set("numpy", string)
#string2 = db.get("numpy")
#array2 = np.fromstring(string, dtype=np.uint8)
#print array2

# test numpy stuff

#num = 100
array = np.array(range(1000), dtype=float)
for i in range(num_operations):
    db.set(i , array.tostring())

stime = time.time()
values = db.mget(range(num_operations))
for value in values:
    a = np.fromstring(value, dtype=float)
etime = time.time()

duration = int((etime - stime) * 1000)
print "Total Numpy Time: %s, (%s ms/getandset)" %(str(duration), str(duration))

#import code; code.interact(local=locals())

# uint8_t*
#char_data = image.getData()
#import code; code.interact(local=locals())

#for kp in keypoints:
    #print kp

# make sure there isn't stale data
db.flushall()
