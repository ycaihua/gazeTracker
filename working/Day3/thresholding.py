import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('/home/atom/9.jpg',0)
img = cv2.medianBlur(img,5)

th2 = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_MEAN_C,\
            cv2.THRESH_BINARY,11,2)

images = [img,th2]

for i in xrange(2):
    plt.subplot(1,2,i+1),plt.imshow(images[i],'gray')
plt.show()
