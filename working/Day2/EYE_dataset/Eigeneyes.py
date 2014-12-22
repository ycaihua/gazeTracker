##
##  Project: Eigen decomposition of eye-images(Eigen_eyes)
##  Authors: Mudit Jain, Dhaivat Bhatt
##  Date: 15/11/2014
##

#Importing necessary packages:-

import numpy as np
import scipy
import SimpleCV
import math
from numpy import *
from scipy import linalg as LA
from SimpleCV import *
import cv2
import os
import time

# Initialization:-

# vector_image --> every row corresponds to an image
vector_image = np.ndarray((10,262144),dtype = int)

# average -->  to compute the average of dataset(images)
average = np.ndarray((512,512),dtype = int) # average -->  to compute the average of dataset(images)

# intermediate_matrix --> to store the deviationof images from average
intermediate_matrix = np.ndarray((512,512),dtype = int)

# It saves covariance matrix of vector_image
covariance = np.ndarray((10,10),dtype = int)

# It saves the final eigen_vectors of all images
Final_eigen_vectors = np.ndarray((262144,10),dtype = int) # To

# Global path of the directory:
global_path = "/home/dhaivat666/EYE_dataset"

#finding the average of 10 images
for i in range(1,11):
    path = global_path + "/Original_data/" + str(i) + ".jpg" # path of the image image_dataset
    img = Image(path) # Loading the image
    img = img.resize(512,512) # resizing the image to square to perform matrix operations
    imgGM = img.getGrayNumpy() # grayscale numpy matrix of an image
    save_path = global_path + "/grayscalenumpy/" + str(i) + ".jpg" # It creates a path variable for saving the grey scale images
    cv2.imwrite(save_path,imgGM) # saving the imgGM(matrix) as an image
    average = imgGM + average # finding the sum of all the image

average = average/10.0 #finding the average image

average_column = np.reshape(average,[262144,1]) # finding the vector for the average image

# finding the deviation from the average image, saved as intermediate matrix

for i in range(1,11):
    path = global_path + "/grayscalenumpy/" + str(i) + ".jpg"
    img = Image(path)
    imgGM = img.getGrayNumpy()
    intermediate_matrix = imgGM - average  #deviation from the average matrix
    save_path = global_path + "/intermediate_matrix/" + str(i) + ".jpg"
    cv2.imwrite(save_path,intermediate_matrix) #saving the intermediate matrix


# finding the matrix of all the images as where each image corresponds to a row and where columns are the pixels of the images

for i in range(1,11):
    path = global_path + "/intermediate_matrix/" + str(i) + ".jpg"
    img = Image(path)
    imgGM = img.getGrayNumpy()
    imgGM = np.reshape(imgGM,[262144])
    vector_image[i-1,:] = imgGM

# Defining the matrix multiplication to avoid broadcasting error

# matrix_multiplication1 --> to multiply vector_image with its transpose

def matrix_multiplication1(A,B):
    element = 0
    final = np.ndarray((10,10),dtype = int)
    for iterate in range(0,10):
        for i in range(0,10):
            for j in range(0,262144):
                element += A[iterate,j]*B[j,i]
            final[iterate,i] = element
            element = 0
    return final

# matrix_multiplication2 --> to multiply the vector_image to the eigen vectors of (xT)*x to get the final eigen vectors of x*(xT).

def matrix_multiplication2(A,B):
    element = 0
    final = np.ndarray((262144,10),dtype = int)
    for iterate in range(0,262144):
        for i in range(0,10):
            for j in range(0,10):
                element += A[iterate,j]*B[j,i]
            final[iterate,i] = element
            element = 0
    return final

#finding the co-variance matrix --> x*(xT)
covariance =  matrix_multiplication1(vector_image, vector_image.transpose())

#Normalization
covariance = covariance/262144.0

# finding the Eigen values and Eigen vectors for covariance
Eigen_values, Eigen_vectors = LA.eig(covariance)

#finding the final eigen vectors by multiplying the eigenvectors with the vector_image transpose
Final_eigen_vectors = matrix_multiplication2(vector_image.transpose() , Eigen_vectors)

#Saving the final eigen vectors as eigen eyes

for i in range(0,10):
    imgGM = np.ndarray((262144),dtype = float)
    imgGM = Final_eigen_vectors[:,i]
    imgGM = np.reshape(imgGM , [512 , 512])
    imgGM = imgGM + average
    save_path = global_path + "/Final_images/" + str(i+1) + ".jpg"
    cv2.imwrite(save_path,imgGM)

# Showing one reference image(Final eigen_image) :-

open_eigen_image = global_path + "/Final_images/" + "1.jpg"
img = Image(open_eigen_image)
img.show()

time.sleep(10)
