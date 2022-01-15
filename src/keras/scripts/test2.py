#!/usr/bin/env python
import rospy
import tensorflow as tf
import numpy as np
from tensorflow import keras
from tensorflow.keras import utils
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras import backend as K
# import sys

import h5py

with h5py.File("/home/roblab/new_catkin_ws/src/keras/scripts/my_model.h5", "r") as fp:
    print(fp.attrs.get("keras_version"))

model = keras.models.load_model('/home/roblab/new_catkin_ws/src/keras/scripts/my_model.h5')

def callback(data):
    print(model.predict(data).argmax())
    
def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("chatter", String, callback)
    rospy.spin()
        
if __name__ == '__main__':
    listener()

# batch_size = 256
# num_classes = 10
# epochs = 50


# img_rows, img_cols = 28,28

# (x_train, y_train),(x_test,y_test) = mnist.load_data()

# if K.image_data_format() == 'channels_first':
#     x_train = x_train.reshape(x_train.shape[0],1,img_rows,img_cols)
#     x_test = x_test.reshape(x_test.shape[0],1,img_rows,img_cols)
#     input_shape = (1,img_rows,img_cols)
# else:
#     x_train = x_train.reshape(x_train.shape[0],img_rows,img_cols,1)
#     x_test = x_test.reshape(x_test.shape[0],img_rows,img_cols,1)
#     input_shape = (img_rows,img_cols,1)
    
# x_train = x_train.astype('float32')
# x_test = x_test.astype('float32')
# x_train /= 255
# x_test /= 255
# print('x_train shape:',x_train.shape)
# print(x_train.shape[0],'train samples')
# print(x_test.shape[0],'test samples')

# y_train = utils.to_categorical(y_train,num_classes)
# y_test = utils.to_categorical(y_test,num_classes)

# print(sys.version)

# model = keras.models.load_model('/home/roblab/new_catkin_ws/src/keras/scripts/my_model.h5')
# print(model.predict(x_test[0].reshape(1,28,28,1)).argmax())