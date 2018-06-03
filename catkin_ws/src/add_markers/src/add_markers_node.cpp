#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <tf/transform_listener.h>

ros::Subscriber odom_subscriber;

 

float delta = 0.4f;
bool first_pick = false;
bool second_pick = false;
bool carring = false;
float firs_goal_position_x = 7.3;
float firs_goal_position_y = 1.3;
float second_goal_position_x = 4.5;
float second_goal_position_y = 0.0;
float check11_x = firs_goal_position_x - delta;
float check11_y = firs_goal_position_y - delta;
float check12_x = firs_goal_position_x + delta;
float check12_y = firs_goal_position_y + delta;
float check21_x = second_goal_position_x - delta;
float check21_y = second_goal_position_y - delta;
float check22_x = second_goal_position_x + delta;
float check22_y = second_goal_position_y + delta;

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{

    float x_pos = msg->pose.pose.position.x;
    float y_pos = msg->pose.pose.position.y;


    // position need to be corrected with tf odom to map

    if(!first_pick) {
        ROS_INFO("ODOM POS ([%f],[%g])", x_pos, y_pos);
    }


    // CHECK WHEN THE ROBOT ENTER THE PICK UP POSITON/ WAIT 5 and set carring to true
    if (x_pos > check11_x && x_pos < check12_x &&
        y_pos > check11_y && y_pos < check12_y)
    {
        ROS_INFO("PICK POSITION REACHED ([%f],[%g])", x_pos, y_pos);
        first_pick = true;
        carring = true;
        }
        if (x_pos > check21_x && x_pos < check22_x &&
            y_pos > check21_y && y_pos < check22_y + delta)
        {
            ROS_INFO("RELEASE POSITION REACHED ([%f],[%g])", x_pos,y_pos);
            second_pick = true;
            first_pick = false;
            carring = false;
        } 

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n;
    ros::Rate r(20);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Subscribe to the /odom topic and call the odom_callback function
    odom_subscriber = n.subscribe("/odom", 1000, odom_callback);
    

    // Set our marker type to be a bottle
    uint32_t shape = visualization_msgs::Marker::MESH_RESOURCE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    // INITALI THE MARKER IS IN THE START POSITIION
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    marker.mesh_resource = "package://add_markers/meshes/bottle.stl";
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 7.3;
    marker.pose.position.y = 2.6;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    while (ros::ok())
    {

    marker.lifetime = ros::Duration();
        // Publish the marker
        while (marker_pub.getNumSubscribers() < 1)
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }

        if (carring) {
            marker.header.frame_id = "/plate_top_link";
            marker.pose.position.x = -0.0;
            marker.pose.position.y = 0.0;
        } else {
            if (first_pick) {
                marker.header.frame_id = "/map";
                marker.pose.position.x = 7.3;
                marker.pose.position.y = 2.6;
            }
            if (second_pick) {
                marker.header.frame_id = "/map";
                marker.pose.position.x = 4.5;
                marker.pose.position.y = 0.0;
            }
        }
        
        marker_pub.publish(marker);

        ros::spinOnce();
    }
    return 0;
}