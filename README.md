# Rosbot_sim Branch

Welcome to the `Rosbot_sim` branch of the Experimental Robotics Laboratory - ROS Package Assignment repository. This branch is dedicated to simulating the Husarion ROSbot 2R for the second assignment of the Experimental Robotics Laboratory course.

## Dependencies

Before running the simulation code in this branch, ensure that you have the following dependencies installed:
**Note:** The repository has been tested on Linux Ubuntu 20.04 LTS with ROS Noetic. 


1. **ROSPlan:**
   - [ROSPlan GitHub Repository](https://github.com/KCL-Planning/ROSPlan.git)

2. **Aruco:**
   - [Aruco GitHub Repository](https://github.com/CarmineD8/aruco_ros.git)

3. **ROSbot:**
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
```

### Make the Package
We'll need to "make" everything in our catkin workspace so that the ROS environment knows about our new package. Execute the given commands in your terminal.

```bash
cd ~/assignment_2_ws
catkin_make
```


Fantastic! The installation process is complete, and now it's time to delve into the exciting world of robot exploration and experimentation. Let the robotics adventure begin! 🤖✨

