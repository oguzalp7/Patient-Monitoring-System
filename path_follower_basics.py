#!/usr/bin/env python
import roslib
import sys
import rospy
import cv2
import numpy as np
from cv_bridge import CvBridge, CvBridgeError
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Image

class PathFollower(object):
	def __init__(self):
		self.bridge_object = CvBridge()
		self.image_sub = rospy.Subscriber("/cv_camera/image_raw", Image, self.camera_callback)
		"""self.velocity_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
		self.twist = Twist()"""
	def camera_callback(self, data):
		try:
			cv_image = self.bridge_object.imgmsg_to_cv2(data, desired_encoding='bgr8')
			"""height, width = cv_image.shape[:2]
			descentre = 160
			rows_to_watch = 20
			crop_img = cv_image[int(height/4):height, 0: width]
			hsv = cv2.cvtColor(crop_img, cv2.COLOR_BGR2HSV)
			lower_hsv = np.array([56, 115, 165])
			higher_hsv = np.array([132, 255, 216])
			mask = cv2.inRange(hsv, lower_hsv, higher_hsv)
			res = cv2.bitwise_and(crop_img, crop_img, mask=mask)
			m = cv2.moments(mask, False)
			try:
				cx, cy = m['m10']/m['m00'], m['m01']/m['m00']
			except ZeroDivisionError:
				cy, cx = height/2, width/2
			cv2.circle(res, (int(cx), int(cy)), 10, (0, 0, 255), -1)
			error = cx - width/2
			self.twist.linear.x = 0.2
			self.twist.angular.z = -float(error)/100
			self.velocity_pub.publish(self.twist)"""
		except CvBridgeError as e:
			print(e)
		cv2.imshow('Surveillance Window', cv_image)
		cv2.waitKey(3)

def main():
	rospy.init_node('path_following_node', anonymous=True)
	path_follower_object = PathFollower()
	
	try:
		rospy.spin()
	except KeyboardInterrupt:
		print('Shutting down')

	
	cv2.waitKey(0)
	cv2.destroyAllWindows()


main()