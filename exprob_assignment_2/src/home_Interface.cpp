#include "../include/exprob_assignment_2/home.h"
#include <unordered_map>
#include <tuple>
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_msgs/GoalStatus.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <string.h>


namespace KCL_rosplan {
	home_Interface::home_Interface(ros::NodeHandle &nh) {}
	
	bool home_Interface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) {

			std::cout << "Going from " << msg->parameters[1].value << " to " << msg->parameters[2].value << std::endl;
			
			
			std::unordered_map<std::string, std::tuple<float,float>> home_position = {{"wp0", std::make_tuple(0.0, 1.0)}};
			
			std::tuple<float,float> home = home_position.at(msg->parameters[2].value);
			
			/*sleep(5);*/

			actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);


			ac.waitForServer();

			// define goal to reach
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.pose.position.x = std::get<0>(home);
			goal.target_pose.pose.position.y = std::get<1>(home);
			goal.target_pose.pose.orientation.w = 1.0;
			goal.target_pose.header.stamp = ros::Time::now();
			goal.target_pose.header.frame_id = "map";
			

			ROS_INFO("===> HOMING <===");
			ac.sendGoal(goal);
			ac.waitForResult();

			if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
				ROS_INFO("Home, home sweet home");
			else
				ROS_INFO("OOPPPSSS something got wrong!!");
			
			ROS_INFO("Action (%s) performed: completed!", msg->name.c_str());
			
			return true;
	}
}


int main(int argc, char **argv) {
	
	ros::init(argc, argv, "gohome_interface", ros::init_options::AnonymousName);	
	ros::NodeHandle nh("~");	
	KCL_rosplan::home_Interface my_aci(nh);
	my_aci.runActionInterface();
	
	return 0;
}