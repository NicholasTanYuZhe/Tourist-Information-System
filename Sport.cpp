/*************************************
Program: Sport.cpp
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#include "Sport.h"

Sport::Sport(int id, string name, int typeID, string address, string phone, string operatingHour)
	: Attraction(id, name, typeID, address, phone, operatingHour)
{
}
void Sport::displayDetail()
{
	cout << "Name = " << name << endl;
	cout << "Address = " << address << endl;
	cout << "Phone = " << phone << endl;
	cout << "Operating Hour = " << operatingHour << endl;
}