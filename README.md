# Rosbot_sim Branch

Welcome to the `Rosbot_sim` branch of the Experimental Robotics Laboratory - ROS Package Assignment repository. This branch is dedicated to simulating the Husarion ROSbot 2R for the second assignment of the Experimental Robotics Laboratory course.

## Dependencies

Before running the simulation code in this branch, ensure that you have the following dependencies installed:
**Note:** The repository has been tested on Linux Ubuntu 20.04 LTS with ROS Noetic. 

1. **ROSPlan:**
   - [ROSPlan GitHub Repository](https://github.com/KCL-Planning/ROSPlan.git)

2. **move_base**
   - [Move_base](http://wiki.ros.org/move_base)

2. **gmapping**
   - [Gmapping](http://wiki.ros.org/gmapping)

3. **Aruco:**
   - [Aruco GitHub Repository](https://github.com/CarmineD8/aruco_ros.git)

4. **ROSbot:**
   - [Rosbot GitHub Repository](https://github.com/husarion/rosbot_ros.git) (noetic)

## Installation

Prepare the work space:
cd ~
mkdir -r assignment_2_ws/src
cd ~/ assignment_2_ws
catkin_make

Clone the repositories mentioned above to your workspace:

```bash
cd ~/assignment_ws/src
git clone https://github.com/KCL-Planning/ROSPlan.git
git clone https://github.com/CarmineD8/aruco_ros.git
gir clone https://github.com/husarion/rosbot_ros.git -b noetic
```
Make sure to follow the installation instructions provided in the respective repositories to set up these dependencies correctly.

Install dependencies:

```bash
cd ~/assignment_2_ws
rosdep install --from-paths src --ignore-src -r -y
```
Build the workspace:

```bash
cd ~/assignment_2_ws
catkin_make
```
Please remember that each time, when you open new terminal window, you will need to load system variables or simply add this command on your .bashrc file.

```bash
source ~/assignment_2_ws/devel/setup.sh
```
### Let your gazebo know the ArUco markers
Add these commands to your .bashrc file 
```bash
export GAZEBO_MODEL_PATH="${CATKIN_ENV_HOOK_WORKSPACE}/../src/aruco_ros/aruco_ros/models/:${GAZEBO_MODEL_PATH}"
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:<PATH_TO_YOUR_assignment_2_ws>/src/aruco_ros/aruco_ros/models
```

### Clone the Aruco Navigation Package

To incorporate this repository into the "src" folder of your recently established Catkin workspace, execute the following command in your terminal:

```bash
git clone https://github.com/Melih199/Exp_rob_assignment_2.git
cd script
chmod +x *py
cd ../launch
chmod +x *bash
```

### Make the Package
We'll need to "make" everything in our catkin workspace so that the ROS environment knows about our new package. Execute the given commands in your terminal.

```bash
cd ~/assignment_2_ws
catkin_make
```
Fantastic! The installation process is complete, and now it's time to delve into the exciting world of robot exploration and experimentation. Let the robotics adventure begin! 🤖✨

## Launch

To run the simulation we need to run following launch files.

**For simulation and SLAM**:
```bash
roslaunch exprob_assignment_2 assignment_2.launch
```
The execution of the launch command will provide us:
-  The gazebo environment of the assignemnt
-  The ROSbot 
-  Gmapping
-  Move_base

**For ROSplan**:
```bash
roslaunch exprob_assignment_2 planning.launch
```
The execution of the launch command will provide us:
-  ROSplan
-  Aruco detector

After launching these files now time to start problem generation, planning, and plan dispatch. For these services we can simply run the following ros commands:

**For problem generation, planning, and plan dispatch**:
```bash
rosservice call /rosplan_problem_interface/problem_generation_server
rosservice call /rosplan_planner_interface/planning_server
rosservice call /rosplan_parsing_interface/parse_plan
rosservice call /rosplan_plan_dispatcher/dispatch_plan
```
Yes we know that it is little bit more commands to execute :) thats why we created the simle .bash file to run these commands.

**For problem generation, planning, and plan dispatch**:
```bash
roscd exprob_assignment_2/launch
./ROSplan_generate
```

**Expected Behavior**

    1- Gazebo and RViz environments will open, displaying the ROSbot within the provided world along with markers.
    2- The ROSbot will autonomously drive toward the first waypoint to detect marker.
    3- Upon reaching the marker, the ROSbot will turn to detect the marker.
    4- Once the marker is found, the ROSbot will move toward the next waypoint to find next marker.
    5- This process repeats until all markers have been found.
    6- After finding all markers, the ROSbot will drive back to the initial position.
    

<img src="https://github.com/Melih199/Exp_rob_assignment_1/blob/Rosbot_aruco_simulation/simulation_node.gif" width="1000" height="800"/>


## Architecture and Pseudocode


 <img src="https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/bea6ec18-fb28-4d73-97be-4d32e31baac7.type" width="500" height="250">


 <img src="https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/b8c52b03-4932-4621-b33b-1b6a228aa500.type" width="500" height="250">

### aruco_detector node 

In this node we used the image information provided from /camera/color/image_raw and /camera/color/camera_info topics to find the ArUco markers.

```python
self.camera_sub = rospy.Subscriber('/camera/color/image_raw', Image, self.image_callback)
self.camera_info_sub = rospy.Subscriber('/camera/color/camera_info', CameraInfo, self.camera_callback)

```

Then we used this information to calculate the marker_center and marker_size.

```python
marker_center_x = (corners[0][0][0][0] + corners[0][0][1][0] +
                                corners[0][0][2][0] + corners[0][0][3][0]) / 4
marker_center_y = (corners[0][0][0][1] + corners[0][0][1][1] +
                                corners[0][0][2][1] + corners[0][0][3][1]) / 4            

marker_center = [marker_center_x, marker_center_y]
            
top_right = [corners[0][0][0][0], corners[0][0][0][1]]
bottom_right = [corners[0][0][3][0], corners[0][0][3][1]]
x_cord = top_right[0] - bottom_right[0]
y_cord = top_right[1] - bottom_right[1]
size = int(np.sqrt(np.power(x_cord, 2) + np.power(y_cord, 2)))
```

Finally the node publishes the marker_center, marker_size, id(provided with ArUco library) camera_center(provided with /camera/color/camera_info topic).

```python
self.aruco_info_pub = rospy.Publisher('aruco_info', Aruco_info, queue_size=10)
...
def camera_callback(self, camera_msg):
        self.camera_center_x = camera_msg.width / 2
        self.camera_center_y = camera_msg.height / 2
...
info_msg = Aruco_info()
info_msg.id = int(ids[0][0])
info_msg.camera_center = camera_center
info_msg.marker_center = marker_center
info_msg.marker_size = [size]            
self.aruco_info_pub.publish(info_msg)
```

### For real robot check the Rosbot_aruco branch !!!
```bash
cd ~/Exp_rob_assignment_1
git checkout Rosbot_aruco
```
This command will change the branch of the repository for real robot. Then follow the instructions given in the readme file.

## Conclusion and Future Improvements

In concluding our Aruco Navigation project, our team has successfully developed a robust system for autonomous robot navigation using Aruco markers. The project's structure and implementation, detailed in the README, lay the foundation for future enhancements and applications.
