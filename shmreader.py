import sysv_ipc
import cv2
import numpy as np


# Create shared memory object
memory = sysv_ipc.SharedMemory(123456)

size = 480, 640, 3
#m = np.zeros(size, dtype=np.uint8) # ?


# Read value from shared memory
frameCount = bytearray(memory.read())

m = np.array(frameCount, dtype=np.uint8 )
m = m.reshape(size)
print m[0]
cv2.imshow('1', m)
cv2.waitKey(0)

# Find the 'end' of the string and strip
i = frameCount.find('\0')
if i != -1:
    frameCount = frameCount[:i]

print str(frameCount)
