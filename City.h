/*************************************
Program: City.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include "Attraction.h"
#include "LinkedList.h"
using namespace std;

class City {
	int id;
	string name;
	LinkedList<Attraction*> Attractions;
public:
	City(int id, string name, LinkedList<Attraction*> Attractions);
	int getID();     //To get the city ID
	int getAttractionLength();     //To get attraction length
	int getAttractionTypeID(int& a);     //To get attraction type ID
	int getAttractionID(int& a);     //To get attraction ID
	string getName() const;     //To get city name
	string getAttractionName(int& a);     //To get attraction name
	string getAttractionAddress(int& a);     //To get attraction address
	string getAttractionNumber(int& a);     //To get attraction phone number
	string getAttractionOperatingHour(int& a);     //To get attraction operating hour
	Attraction* getAttraction(int& a);     //To get the attraction
	void display();     //To display city
	void displayAttraction();     //To display attraction
	void displayAttractionTypeID(int a);     //To display attraction that sort by attraction type ID
	void displayAttractionDetail(int a);     //To display the detail of attraction
	bool getAttractionEmpty();     //To get the attraction is empty or not
	friend bool operator<=(const City& c1, const City& c2);     //To allow comparison between City type with another City type in sort insert function
	friend bool operator>=(const City& c1, const City& c2);     //To allow comparison between City type with another City type in sort insert function
};

#endif