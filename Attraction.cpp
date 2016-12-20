/*************************************
Program: Attraction.cpp
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#include "Attraction.h"

Attraction::Attraction(int id, string name, int typeID, string address, string phone, string operatingHour)
	: id(id), name(name), typeID(typeID), address(address), phone(phone), operatingHour(operatingHour)
{

}

void Attraction::display()
{
	cout << "ID = " << id << ". Name = " << name << ". Type ID = " << typeID << endl;
}

int Attraction::getTypeID()
{
	return typeID;
}

int Attraction::getID()
{
	return id;
}

string Attraction::getName()
{
	return name;
}

string Attraction::getAddress()
{
	return address;
}

string Attraction::getNumber()
{
	return phone;
}

string Attraction::getOperatingHour()
{
	return operatingHour;
}

bool operator<=(const Attraction& a1, const Attraction& a2)
{
	return a1.name <= a2.name;
}

bool operator>=(const Attraction& a1, const Attraction& a2)
{
	return a1.name>= a2.name;
}