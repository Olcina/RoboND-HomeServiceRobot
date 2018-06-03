#!/bin/sh

SOURCE_CMD="source /home/workspace/catkin_ws/devel/setup.bash"


terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo turtlebot_world.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo amcl_demo.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_rviz_launchers view_navigation.launch " & sleep 5

terminator -e "$SOURCE_CMD; rosrun pick_objects pick_objects_node " & sleep 5

