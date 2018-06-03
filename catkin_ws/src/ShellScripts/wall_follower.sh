#!/bin/sh

SOURCE_CMD="source ../../devel/setup.bash"


terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo turtlebot_world.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_gazebo gmapping.launch " & sleep 5

terminator -e "$SOURCE_CMD; roslaunch turtlebot_rviz_launchers view_navigation.launch " & sleep 5

terminator -e "$SOURCE_CMD; rosrun wall_follower wall_follower_node" & sleep 5


