#!/bin/sh

SOURCE_CMD="source ~/RoboND-HomeServiceRobot/catkin_ws/devel/setup.bash"


terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo turtlebot_world.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo gmapping_demo.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_rviz_launchers view_navigation.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_teleop keyboard_teleop.launch" & sleep 5


