/*************************************
Program: Flight.cpp
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#include "Flight.h"

Flight::Flight(int V)
{
    this->V = V;
    adj = new LinkedStack<int>[V];
}
 
void Flight::addEdge(int v, int w)
{
    adj[v].push(w); // Add w to v’s list.
}
 
bool Flight::isReachable(int s, int d)
{
    while (!flightStack.isEmpty())     //To make sure the flightStack is empty before proceeding
        flightStack.pop();
    
    bool *visited = new bool[V];     // Mark all the vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    LinkedStack<int> stack;     //Create stack for DFS
 
    visited[s] = true;     // Mark the current node as visited and push it
    stack.push(s);

    while (!stack.isEmpty())
    {
        bool result = false;     //To make sure if the adjacent city of the current city is all visited, pop out from the stack
        s = stack.peek();
        flightStack.push(s);
        stack.pop();

        while (!adj[s].isEmpty())     // Get all adjacent vertices of the poped vertex s
        {
            if (adj[s].peek() == d)     // If this adjacent node is the destination node, then return true
            {
                stack.push(adj[s].peek());
                flightStack.push(adj[s].peek());
                return true;
            }
            
            if (!visited[adj[s].peek()])     // If a adjacent has not been visited, then mark it visited and push into stack
            {
                result = true;
                visited[adj[s].peek()] = true;
                stack.push(adj[s].peek());
                adj[s].pop();
            }
            else     //If the city visited, then just pop and do not insert into the stack
            {
                adj[s].pop();
            }
        }
        if(!result)     //If the adjacent city is all visited and backtrack, pop the stack
            flightStack.pop();
    }
    return false;     //return false if DFS fail to reach destination city
}

int Flight::getStack()
{
    return flightStack.peek();
}

void Flight::removeStack()
{
    flightStack.pop();
}

bool Flight::isEmptyStack()
{
    return flightStack.isEmpty();
}