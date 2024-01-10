# Rosbot_sim Branch

Welcome to the `Rosbot_sim` branch of the Experimental Robotics Laboratory - ROS Package Assignment repository. This branch is dedicated to work-on the real robot Husarion ROSbot 2R for the second assignment of the Experimental Robotics Laboratory course.

## Dependencies

Before running the simulation code in this branch, ensure that you have the following dependencies installed:
**Note:** The repository has been tested on Linux Ubuntu 20.04 LTS with ROS Noetic. 

1. **ROSPlan:**    - [ROSPlan GitHub Repository](https://github.com/KCL-Planning/ROSPlan.git)
2. **move_base** - [Move_base](http://wiki.ros.org/move_base)
2. **gmapping**  - [Gmapping](http://wiki.ros.org/gmapping)
3. **Aruco:**    - [Aruco GitHub Repository](https://github.com/CarmineD8/aruco_ros.git)


## Connection and Installation

Connect the ROSbot with screen, keyboard and mouse. Thats it!

Prepare the work space:
```bash
cd ~
mkdir -r assignment_2_ws/src
cd ~/ assignment_2_ws
catkin_make
```

Clone the repositories mentioned above to your workspace:

```bash
cd ~/assignment_ws/src
git clone https://github.com/KCL-Planning/ROSPlan.git
git clone https://github.com/CarmineD8/aruco_ros.git
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
Please remember that each time, when you open new terminal window, you will need to load system variables or simply add this command on ROSbot .bashrc file.

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
roscd exprob_assignment_2
git checkout Rosbot_real
```

### Make the Package
We'll need to "make" everything in our catkin workspace so that the ROS environment knows about our new package. Execute the given commands in your terminal.

```bash
cd ~/assignment_2_ws
catkin_make
```
Fantastic! The installation process is complete, and now it's time to delve into the exciting world of robot exploration and experimentation. Let the robotics adventure begin! 🤖✨

### SSH Connection
- First of all connect the robot to router same with your laptop.
- Check the ip adress of the ROSbot with this command:
 ```bash
   ifconfig
 ```
- Add these commands to your .bashrc file:
 ```bash
  #ROSBOT << Real Robot >>
  export ROS_MASTER_URI=http://<IP_of_ROSbot>:11311
  export ROS_IP=<IP_of_ROSbot>
 ```
- Unplug the connections(screen,keyboard,mouse)
- On your laptop login in ssh to husarion@<IP_of_ROSbot> passport:husarion
   ```bash
     ssh husarion@<IP_of_ROSbot>
   ```
- 🤖✨🤖✨🤖✨ We are ready!!! Put the robot on the prepared environment🤖✨🤖✨🤖✨


## Launch

To run the simulation we need to run following launch files.

The execution of the launch command of the all.launch file will provide us necessary nodes to deal with ROSbot such as: lidar and camera...
**For real robot**:
```bash
roslaunch tutorial_pkg all.launch
```

**For simulation and SLAM**:
```bash
roslaunch exprob_assignment_2 gmapping.launch
roslaunch exprob_assignment_2 move_base.launch
```
The execution of the launch command will provide us: 
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
    



https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/fb49d170-e1ca-4d9e-8cc0-d4099d288b3d

https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/759f1c8e-c75b-4eb1-b756-7192334f6f4f

https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/b3619014-befc-45cf-8cb5-0189420a8bed

## Architecture and Pseudocode


 <img src="https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/bea6ec18-fb28-4d73-97be-4d32e31baac7.png" width="500" height="400">


 <img src="https://github.com/Melih199/Exp_rob_assignment_2/assets/58879182/b8c52b03-4932-4621-b33b-1b6a228aa500.png" width="500" height="400">

## PDDL
## Domain ([source](./exprob_assignment_2/pddl/domain.pddl))

### goto_waypoint action 
This action represents a robot navigating from one waypoint to another with a fixed duration. It specifies the initial condition that the robot must be at the starting waypoint and defines the effects after the action is executed, including the robot's new position, marking the target waypoint as visited, and updating the count of reached waypoints.

### search_marker
Robot searching for a marker at a specific waypoint. It requires the robot to be at the designated waypoint and for the marker to be visible at the beginning of the action. The effects include marking the specific marker as found and updating the count of detected markers.

### home
This durative action represents the robot returning home. The action requires the robot to be at the specified current waypoint, with no reached waypoints or detected markers. After executing the action, the robot moves to the home waypoint, performs homing, and marks the home waypoint as visited.

## Problem ([source](./exprob_assignment_2/pddl/problem.pddl))
The goal of this problem is to navigate the robot to visit all waypoints, find all markers, and finally perform homing at the initial waypoint wp0. The initial state provides the starting conditions of the robot's position, visibility of markers, and initial counts of reached waypoints and detected markers

## Plan ([source](./exprob_assignment_2/pddl/plan.pddl))
------------------------

### goto_waypoint Interface ([source](./exprob_assignment_2/src/goto_waypoint_Interface.cpp))
Action interface for a "goto_waypoint" action using the MoveBase package. The action aims to make a robot move from one waypoint to another in a simulated environment. The node subscribes to action dispatch messages, received from the ROSPlan framework, to execute the specified waypoint movements.

```cpp
class goto_waypoint_Interface:
    constructor(node_handle):
        initialize

    function concreteCallback(message):
        extract information from message
        create MoveBaseGoal based on target waypoint
        create SimpleActionClient for /move_base
        send goal to MoveBase
        wait for result
        log success/failure of the action
        return true

main function:
    initialize ROS node
    create goto_waypoint_Interface instance
    run action interface


```
### home Interface ([source](./exprob_assignment_2/src/home_Interface.cpp))
Action interface for a "home" action. The action aims to make a robot move to a predefined home position. Similar to the goto_waypoint interface, this node subscribes to action dispatch messages, received from the ROSPlan framework, to execute the specified "home" action.

```cpp
class home_Interface:
    constructor(node_handle):
        initialize

    function concreteCallback(message):
        extract information from message
        retrieve predefined home position based on waypoint
        create SimpleActionClient for move_base
        set goal to predefined home position
        send goal to move_base
        wait for result
        log success/failure of the action
        return true

main function:
    initialize ROS node
    create home_Interface instance
    run action interface



```
### search_marker Interface ([source](./exprob_assignment_2/src/search_marker_Interface.cpp))
Action interface for a "search_marker" action. The action aims to make a robot search for a specific Aruco marker. The code subscribes to Aruco marker information messages (aruco_info) to detect the currently visible marker and then adjusts the robot's orientation until the desired marker is detected.

```cpp
global detected_markerID
global search_markerID
global cmd_vel_pub

function aruco_callback(message):
    update detected_markerID with the ID of the detected Aruco marker

class search_marker_Interface:
    constructor(node_handle):
        initialize

    function concreteCallback(message):
        extract information from message
        set search_markerID based on specified marker name
        adjust robot's orientation until desired marker is detected
        publish velocity commands to control robot's rotation
        log completion of the action
        return true

main function:
    initialize ROS node
    subscribe to aruco_info topic with aruco_callback
    advertise cmd_vel publisher
    create search_marker_Interface instance
    run action interface



```

### aruco_detector node ([source](./exprob_assignment_2/script/aruco_detector.py))

In this node we used the image information provided from /camera/color/image_raw and /camera/color/camera_info topics to find the ArUco markers.

```python
self.camera_sub = rospy.Subscriber('/camera/rgb/image_raw', Image, self.image_callback)
self.camera_info_sub = rospy.Subscriber('/camera/rgb/camera_info', CameraInfo, self.camera_callback)

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



