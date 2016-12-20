/*************************************
Program: Flight.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include "LinkedStack.h"
using namespace std;

class Flight {
    int V;    // No. of vertices
    LinkedStack<int> *adj;    // Pointer to an array containing adjacency lists
    LinkedStack<int> flightStack;
public:
    Flight(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to Flight
    bool isReachable(int s, int d);  // returns true if there is a path from s to d
    int getStack();
    void removeStack();
    bool isEmptyStack();
};

#endif