#!/bin/sh

terminator -e "gazebo" &

sleep 5

terminator -e "source /opt/ros/kinetic/setup.bash; roscore" &

sleep 5

terminator -e "rosrun rviz rviz"
