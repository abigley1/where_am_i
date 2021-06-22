#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <string>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
     // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    client.call(srv);
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
  // ROS_INFO_STREAM("looping over image") ;
    int white_pixel = 255;
    bool no_ball = true;
    double pixel_pos = 0; 
    
    //looping
    
    for (int i = 0; i < img.height * img.step; i++) {
       if (img.data[i] == white_pixel){

            no_ball = false;
            
	    pixel_pos = (i % img.width) / (800.001);
	    break;
       }}	  
            if (pixel_pos >= 0 & pixel_pos < .33) { //drive left
                drive_robot(0, 0.5);     
            }
            if (pixel_pos > .33 & pixel_pos < .66){ //srive stright 
                drive_robot(1, 0);
            }
            if (pixel_pos > .66 & pixel_pos <= 1){ //drive right
                drive_robot(0, -0.5);
            }
			  
			   
          if (no_ball == true){ //stop if no ball
                drive_robot(0,0);
		ROS_INFO_STREAM("NO BALL");
	  }
	
}
    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera


int main(int argc, char** argv){
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
