#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//TODO: Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"
#include <string>

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities

bool handle_drive_request(ball_chaser::DriveToTarget::Request& req , ball_chaser::DriveToTarget::Response& res)
{  
    
    geometry_msgs::Twist mv_cmd;
    mv_cmd.linear.x = req.linear_x;
    mv_cmd.angular.z = req.angular_z;
    motor_command_publisher.publish(mv_cmd);
    std::string lin_x = std::to_string(req.linear_x);
    std::string ang_z = std::to_string(req.angular_z);
    res.msg_feedback = "Commanded velocities X:"+lin_x+" Z:"+ang_z;
    ROS_INFO_STREAM(res.msg_feedback);
    
    
    
} 
        
         
       
    

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function              
    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot" , handle_drive_request);
                      
    //ros::Subscriber sub1 = n.subscriber("/ball_chaser/joint_states", 10, handle_drive_request)
                      
    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values

    ros::spin();

    return 0;
}
