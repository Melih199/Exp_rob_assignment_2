#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <motion_plan/PlanningAction.h>
#include "../include/exprob_assignment_2/goto_waypoint.h"
#include <move_base_msgs/MoveBaseAction.h>


namespace KCL_rosplan {

	goto_waypoint_Interface::goto_waypoint_Interface(ros::NodeHandle &nh) {
	// here the initialization
	}

	bool goto_waypoint_Interface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {
		// here the implementation of the action
		std::cout << "Going from " << msg->parameters[1].value << " to " << msg->parameters[2].value << std::endl;
		
		/*sleep(5);*/
		
		actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("/move_base", true);
		move_base_msgs::MoveBaseGoal goal;	
  
		ac.waitForServer();

		if(msg->parameters[2].value == "wp0"){
		goal.target_pose.pose.position.x = 0.0;
		goal.target_pose.pose.position.y = 1.0;
		goal.target_pose.pose.orientation.w = 0.0;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		
		}

		else if (msg->parameters[2].value == "wp1"){
		goal.target_pose.pose.position.x = 6.0;
		goal.target_pose.pose.position.y = 2.0;
		goal.target_pose.pose.orientation.w = 1.0;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		
		}

		else if (msg->parameters[2].value == "wp2"){
		goal.target_pose.pose.position.x = 7.0;
		goal.target_pose.pose.position.y = -5.0;
		goal.target_pose.pose.orientation.w = 1.0;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		
		}

		else if (msg->parameters[2].value == "wp3"){
		goal.target_pose.pose.position.x = -3.0;
		goal.target_pose.pose.position.y = -8.0;
		goal.target_pose.pose.orientation.w = 1.0;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		
		}
		
		else if (msg->parameters[2].value == "wp4"){
		goal.target_pose.pose.position.x = -7.0;
		goal.target_pose.pose.position.y = 1.5;
		goal.target_pose.pose.orientation.w = 1.0;
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();		
		}		
		
		
		ROS_INFO("===> GOTO_WAYPOINT <===");
		ac.sendGoal(goal);		
		ac.waitForResult();
		
		if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			ROS_INFO("Position reached");
		else
			ROS_INFO("OOPPPSSS something got wrong!");
				
     	ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
	
		return true;	
		
	}
}
int main(int argc, char **argv) {
	
	ros::init(argc, argv, "goto_waypoint_action", ros::init_options::AnonymousName);
	ros::NodeHandle nh("~");
	KCL_rosplan::goto_waypoint_Interface my_aci(nh);
	my_aci.runActionInterface();
	return 0;
}

