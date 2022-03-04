#!/usr/bin/env python
import rospy
import numpy as np

from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from std_msgs.msg import Int32
import cv2


pub = rospy.Publisher('chatter', Int32, queue_size=10)
pub2 = rospy.Publisher('afterImage', Image, queue_size=10)
before = None
MAX_AREA_LIMIT = 2000
MIN_AREA_LIMIT = 500

def callback(msg):
    try:
        global before
        bridge = CvBridge()
        cv_array = bridge.imgmsg_to_cv2(msg,"mono8")
        cv_array = cv2.resize(cv_array,(100,100))
        if before is None:
            before = cv_array.copy().astype('float')
        # before = cv_array.copy().astype('float')
        cv2.accumulateWeighted(cv_array, before, 0.5)
        mdframe = cv2.absdiff(cv_array, cv2.convertScaleAbs(before))
        _, thresh = cv2.threshold(mdframe, 3, 255, cv2.THRESH_BINARY)
        _, contours, hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        max_area = 0
        target = contours[0]

        for cnt in contours:
            area = cv2.contourArea(cnt)
            if max_area < area and area < MAX_AREA_LIMIT and area > MIN_AREA_LIMIT:
                max_area = area
                target = cnt

        if max_area <= MIN_AREA_LIMIT:
            areaframe = cv_array
            ans = 0
        else:
            x, y, width, height = cv2.boundingRect(target)
            areaframe = cv2.rectangle(cv_array, (x, y),(x + width, y + height), (0,255,0), 2)
            ans = x + width/2
        pub.publish(ans)
        image_message = bridge.cv2_to_imgmsg(areaframe.astype('u1'), encoding="mono8")
        pub2.publish(image_message)
 
    except Exception, err:
        rospy.logerr(err)
    
def listener():
    rospy.init_node('movecatch', anonymous=True)
    rospy.Subscriber("/usb_cam/image_raw",Image , callback)
    rospy.spin()
        
if __name__ == '__main__':
    listener()