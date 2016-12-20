/*************************************
Program: City.cpp
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#include "City.h"
#include "Attraction.h"
#include "LinkedList.h"

City::City(int id, string name, LinkedList<Attraction*> Attractions) : id(id), name(name), Attractions(Attractions)
{
	
}
int City::getID()
{
	return id;
}
string City::getName () const
{
	return name;
}
int City::getAttractionLength()
{
	return Attractions.getLength();
}
int City::getAttractionTypeID(int& a)
{
	return Attractions[a]->getTypeID();
}
int City::getAttractionID(int& a)
{
	return Attractions[a]->getID();
}
string City::getAttractionName(int& a)
{
	return Attractions[a]->getName();
}
string City::getAttractionAddress(int& a)
{
	return Attractions[a]->getAddress();
}
string City::getAttractionNumber(int& a)
{
	return Attractions[a]->getNumber();
}
string City::getAttractionOperatingHour(int& a)
{
	return Attractions[a]->getOperatingHour();
}
bool City::getAttractionEmpty()
{
	return Attractions.isEmpty();
}
Attraction* City::getAttraction(int& a)
{
	return Attractions[a];
}
void City::display()
{
	cout << "ID = " << id << ". Name = " << name << "." << endl;
}
void City::displayAttraction()
{
	for(int i=1; i<Attractions.getLength()+1; i++)
		Attractions[i]->display();
}
void City::displayAttractionTypeID(int a)
{
	for(int i=1; i<Attractions.getLength()+1; i++)
		if(a == Attractions[i]->getTypeID())            // To sort out the type id
			Attractions[i]->display();
}
void City::displayAttractionDetail(int a)
{
	for(int i=1; i<Attractions.getLength()+1; i++)
		if (a == Attractions[i]->getID())             // To choose the sorted out list
			Attractions[i]->displayDetail();
}
bool operator<=(const City& c1, const City& c2)
{
	return c1.name <= c2.name;
}
bool operator>=(const City& c1, const City& c2)
{
	return c1.name >= c2.name;
}