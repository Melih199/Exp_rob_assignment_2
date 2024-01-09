# Experimental Robotics Laboratory - ROS Package Assignment

This repository contains the ROS package implementation for the second assignment of the Experimental Robotics Laboratory course at the University degli Studi di Genova. The assignment focuses on utilizing various ROS packages to achieve a set of tasks with a mobile robot, specifically the Husarion ROSbot 2R, in both simulation and real-world scenarios.

## Assignment Requirements

The assignment outlines the following key requirements:

1. A mobile robot equipped with a camera is required to locate and identify markers within a predefined environment and return to its initial position.
2. The positions of the markers are specified as follows:
   - Marker 11: Visible from position (x = 6.0, y = 2.0)
   - Marker 12: Visible from position (x = 7.0, y = -5.0)
   - Marker 13: Visible from position (x = -3.0, y = -8.0)
   - Marker 15: Visible from position (x = -7.0, y = -1.5)
3. The ROSPlan framework is to be employed for planning the robot's actions.
4. The implementation must cover both simulation (using the provided world file "assignment2.world") and the real robot.

## Implementation Overview

The fulfillment of these requirements is structured as follows:

- **Main Branch:**
  - Implements code for simulating the Husarion ROSbot 2R. The architecture is organized around a node responsible for plan generation using the ROSPlan framework, a node for handling vision data through the aruco package, and three nodes implementing actions for plan execution.

- **Rosbot Branch:**
  - Adapts the code from the main branch to drive the real Husarion ROSbot 2R, ensuring successful completion of the assigned tasks.

## Repository Structure

The repository includes necessary dependencies such as the ROSPlan framework, aruco package, and the rosbot_description package, offering a comprehensive solution for the Experimental Robotics Laboratory assignment.
