# Robot-Maze-OOP_Auto

This project is a simple console based robot maze continuation of the [Robot-Maze](https://github.com/AldaniP/Robot-Maze) project implemented in C++ using OOP. In this project the robot can automatically find the finish point or the one marked ($)

# How To Use

The first line of input should contain two integers N and M, representing the dimensions of the arena.

(*) : Start position of the robot

($) : Finish position

(#) : Visited position during pathfinding

(o) : Obstacle 

# Example
- Input 1
  ```
  4 4
  $.o.
  o..o
  *o.o
  ....
  ```
- Output 1
  ```
  4 4
  *#o.
  o##o
  #o#o
  ###.
  Robot mencapai Finish
  ```
- Input 2
  ```
  4 4
  $o..
  o..o
  *o.o
  ....
  ```
- Output 2
  ```
  Robot Tidak Mencapai Finish
  ```
  
