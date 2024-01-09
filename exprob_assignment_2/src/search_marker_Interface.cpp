#include "ros/ros.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <motion_plan/PlanningAction.h>
#include "../include/exprob_assignment_2/search_marker.h"
#include "exprob_assignment_2/Aruco_info.h"
#include <move_base_msgs/MoveBaseAction.h>



int detected_markerID;
int search_markerID;
ros::Publisher cmd_vel_pub;
ros::Subscriber marker_search_sub;



void aruco_callback(const exprob_assignment_2::Aruco_info::ConstPtr& msg){
	

	detected_markerID = msg->id;
}

namespace KCL_rosplan {

	search_marker_Interface::search_marker_Interface(ros::NodeHandle &nh) {
	// here the initialization
	}

	bool search_marker_Interface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
		// here the implementation of the action
		std::cout << "I am on way point: " << msg->parameters[1].value << "and serching marker: " << msg->parameters[2].value << std::endl;
			
		
		if(msg->parameters[2].value == "m11"){
		
			search_markerID= 11;
			ROS_INFO("looking for 11");	
		}

		else if (msg->parameters[2].value == "m12"){
		
			search_markerID= 12;
			ROS_INFO("looking for 12");		
		}

		else if (msg->parameters[2].value == "m13"){
			
			search_markerID= 13;
			ROS_INFO("looking for 13");	
		}

		else if (msg->parameters[2].value == "m15"){
		
			search_markerID= 15;
			ROS_INFO("looking for 15");		
		}
			
				
		ROS_INFO("detected Id is %d and looking for %d", detected_markerID, search_markerID);
		
		geometry_msgs::Twist cmd_vel;
		cmd_vel.angular.z = 0.4;

		while (search_markerID != detected_markerID)
		{
			ROS_INFO("Searching marker id: %d - detected marker id: %d", search_markerID, detected_markerID);
			cmd_vel_pub.publish(cmd_vel);
			ros::Duration(0.08).sleep();
		}

		cmd_vel.angular.z = 0.0;
		cmd_vel_pub.publish(cmd_vel);
	
		ROS_INFO("===> SEARCH_MARKER <===");	
     	ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
		return true;
	
	}
	
}

int main(int argc, char **argv) {
	
	ros::init(argc, argv, "search_marker_action", ros::init_options::AnonymousName);
	
	ros::NodeHandle nh;
	
	ros::Subscriber marker_search_sub = nh.subscribe("aruco_info", 100, aruco_callback);
	
	cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
	
		
	KCL_rosplan::search_marker_Interface my_aci(nh);
	my_aci.runActionInterface();
	return 0;
}

