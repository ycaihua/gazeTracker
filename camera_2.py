import numpy as np
import cv2

cap = cv2.VideoCapture(0)
eye_cascade = cv2.CascadeClassifier('/home/atom/Desktop/haarcascade_eye_tree_eyeglasses.xml')


while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    eyes = eye_cascade.detectMultiScale(gray)
    for (ex,ey,ew,eh) in eyes:
        cv2.rectangle(frame,(ex,ey),(ex+ew,ey+eh),(255,255,0),2)
        roi_gray = gray[ey:ey+eh, ex:ex+ew]
    #    ret,thresh = cv2.threshold(roi_gray,127,255,0)
    #    contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    #    img= cv2.drawContours(roi_gray,contours,-1,(0,255,0),3)

        cv2.imshow('alpha',roi_gray)




    # Display the resulting frame
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
