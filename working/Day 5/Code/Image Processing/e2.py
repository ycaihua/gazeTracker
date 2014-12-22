import numpy as np
import cv2

im = cv2.imread('/home/atom/Desktop/srujana/Day3/5.jpg')
print im.shape #check if the image is loaded correctly
imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
img= cv2.drawContours(im,contours,-1,(0,255,0),3
cv2.imshow('image',im)
k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()
elif k == ord('s'): # wait for 's' key to save and exit
    cv2.imwrite('messigray.png',img)
    cv2.destroyAllWindows()
