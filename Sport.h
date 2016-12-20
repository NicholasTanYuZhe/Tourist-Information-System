/*************************************
Program: Sport.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef SPORT_H
#define SPORT_H

#include <iostream>
#include <string>
#include "Attraction.h"
using namespace std;

class Sport : public Attraction {
public:
	Sport(int id, string name, int typeID, string address, string phone, string operatingHour);
	void displayDetail();
};

#endif