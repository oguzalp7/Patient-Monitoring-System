#!/usr/bin/env python

# importing modules
import roslib
import sys
import rospy
import cv2
import numpy as np

# ROS Message Protocols
from cv_bridge import CvBridge, CvBridgeError 
from sensor_msgs.msg import Image

# Camera Listener Class
class PmsCamera(object):
	def __init__(self):
		self.bridge_object = CvBridge()  # Creating CvBridge instance 
		self.image_sub = rospy.Subscriber("/cv_camera/image_raw", Image, self.camera_callback) # Subscriber to Camera Payload that publishes from socket
	# Subscriber Callback
	def camera_callback(self, data):
		try:
			cv_image = self.bridge_object.imgmsg_to_cv2(data, desired_encoding='bgr8')  # The image object that is the same thing with regular opencv projects.
			# only difference is that we're receiving the camera payload from another computers camera.
			# [OPTIONAL] Image processing algorithms is running from here.
			# I did not implemented any image processing in this project.
			# I aim to create a system not a program.
		except CvBridgeError as e:
			print(e)
		cv2.imshow('Surveillance Window', cv_image)  # dislay the result.
		cv2.waitKey(3)

def main():
	rospy.init_node('patient_surveillance_node', anonymous=True)  # node initialization
	camera_listener_object = PmsCamera()  # camera listener object
	try:
		rospy.spin()  # run the Subscriber callback
	except KeyboardInterrupt:
		print('Shutting down')

	
	cv2.waitKey(0)
	cv2.destroyAllWindows()


main()
