/*************************************
Program: Attraction.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <iostream>
#include <string>
using namespace std;

class Attraction {
	int id, typeID;
protected:
	string name, address, phone, operatingHour;
public:
	Attraction(int id = 0, string name = "", int typeID = 0, string address = "", string phone = "", string operatingHour = "");
	void display();     //To display the attraction
	virtual void displayDetail() = 0;
	int getTypeID();     //To get the attraction type ID
	int getID();     //To get the attraction ID
	string getName();     //To get the attraction name
	string getAddress();     //To get the attraction address
	string getNumber();     //To get the attraction number
	string getOperatingHour();     //To get the attraction operating hour
	friend bool operator<=(const Attraction& a1, const Attraction& a2);     //To compare smaller than or equal for attraction inside the sort insert function
	friend bool operator>=(const Attraction& a1, const Attraction& a2);     //To compare greater than or equal for attraction inside the sort inside function
};

#endif