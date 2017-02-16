#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def get_message(str):
	rospy.loginfo("%s",str)

def sender():

	while not rospy.is_shutdown():

		input_line = raw_input(">>")

		if(input_line == ''):
			print("")

		else:
			rospy.loginfo("Send << " + input_line)
			pub.publish("Received >> "+ input_line)


if __name__ == '__main__':
	rospy.init_node('chatter_node')
	pub = rospy.Publisher('chatter1', String, queue_size=10)
	sub = rospy.Subscriber('chatter2', String, get_message)

	sender()

