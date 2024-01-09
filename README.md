## Installation

Prepare the work space:
cd ~
mkdir -r assignment_ws/src
cd ~/ assignment_ws
catkin_make

Clone this repository to your workspace:

```bash
cd ~/assignment_ws/src
git clone https://github.com/husarion/rosbot_ros.git -b noetic
```
and follow the instructions given on husarion/rosbt_ros branch noetic.

Install dependencies:

```bash
cd ~/assignment_ws
rosdep install --from-paths src --ignore-src -r -y
```
Build the workspace:

```bash
cd ~/assignment_ws
catkin_make
```
From this moment you can use rosbot simulations. Please remember that each time, when you open new terminal window, you will need to load system variables or simply add this command on your .bashrc file.

```bash
source ~/assignment_ws/devel/setup.sh
```
### Clone the Aruco Navigation Package

To incorporate this repository into the "src" folder of your recently established Catkin workspace, execute the following command in your terminal:

```bash
git clone https://github.com/Melih199/Exp_rob_assignment_1.git
cd script
chmod +x *py
```

### Make the Package
We'll need to "make" everything in our catkin workspace so that the ROS environment knows about our new package. Execute the given commands in your terminal.

```bash
cd ~/assignment_ws
catkin_make
```

### Let your gazebo know the ArUco markers
Add these commands to your .bashrc file 
```bash
export GAZEBO_MODEL_PATH="${CATKIN_ENV_HOOK_WORKSPACE}/../src/Exp_rov_assignment_1/assignment_1/models/:${GAZEBO_MODEL_PATH}"
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:<PATH_TO_YOUR_assignment_ws>/src/Exp_rov_assignment_1/assignment_1/models
```
Fantastic! The installation process is complete, and now it's time to delve into the exciting world of robot exploration and experimentation. Let the robotics adventure begin! 🤖✨
