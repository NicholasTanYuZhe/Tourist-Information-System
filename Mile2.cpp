/*************************************
Program: Mile2.cpp
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#include <iostream>
#include <fstream>     //To save and load text file
#include <cstdlib>     //To use atoi & system("cls") function
#include <sstream>     //To use istringstream function
#include <string>     //To use string
#include <conio.h>     //To use _getch() function
#include "LinkedList.h"
#include "LinkedStack.h"
#include "City.h"
#include "Attraction.h"
#include "Sport.h"
#include "Culture.h"
#include "Shopping.h"
#include "Flight.h"
using namespace std;

int convertStringToInt(string input)
{
	int output;
	if (!(istringstream(input) >> output))
		output = 0;
	return output;
}

bool saveFile(LinkedList<City>& Cities, bool askName)
{
	ofstream saveFile;
	string filename;
	if(!askName)
	{
		cout << "Please enter a file name to save city and attraction detail =>";
		getline(cin, filename);
	}
	else
		filename = "Name.txt";
	saveFile.open(filename);
 	if(saveFile.is_open())
 	{
 		for(int i=1; i<Cities.getLength()+1; i++)
 		{
			saveFile << Cities[i].getID() << '\t';
 			saveFile << Cities[i].getName() << '\n';
 			for(int j=1; j<Cities[i].getAttractionLength()+1; j++)
 			{
 				saveFile << Cities[i].getAttractionTypeID(j) << '\t';
 				saveFile << Cities[i].getAttractionID(j) << '\t';
 				saveFile << Cities[i].getAttractionName(j) << '\t';
 				saveFile << Cities[i].getAttractionAddress(j) << '\t';
 				saveFile << Cities[i].getAttractionNumber(j) << '\t';
 				saveFile << Cities[i].getAttractionOperatingHour(j);
 				if(Cities[i].getAttractionTypeID(j) == 2)
 				{
 					Culture *culture = dynamic_cast<Culture*>(Cities[i].getAttraction(j));
 					saveFile << '\t' << culture->getEntranceFee();
 				}
 				saveFile << '\n';
 			}
 			saveFile << '\n';
 		}
    	saveFile.close();
    	if(!askName)
    		cout << "Save to " << filename << " success.\n";
    	return true;
 	}
 	else
		return false;
}

bool loadFile(LinkedList<City>& Cities, LinkedList<Attraction*>& Attraction, bool askName)
{
	ifstream loadFile;
 	string filename, record, typeID, ID, name, address, number, operatingHour, entranceFee, cityName, cityID;
	Attraction.clear();
	Cities.clear();
	if(!askName)
	{
		cout << "Please enter a file name to load city and attraction detail =>";
		getline(cin, filename);
	}
	else
		filename = "Name.txt";
	loadFile.open(filename);
	if(loadFile.good())     //To check the file can be open or not
 	{
 		while(getline(loadFile, record, '\n'))     //To get the first line of information of the city and the city id
 		{
 			istringstream iss(record);
 			getline(iss, cityID, '\t');
 			getline(iss, cityName, '\t');

     		while(getline(loadFile, record, '\n'))     //To get the first city attractions
     		{
     			if(record.empty())     //To check the line is empty or not
     				break;
     			entranceFee = "";
     			istringstream iss(record);
     			getline(iss, typeID, '\t');
     			getline(iss, ID, '\t');
     			getline(iss, name, '\t');
     			getline(iss, address, '\t');
     			getline(iss, number, '\t');
     			getline(iss, operatingHour, '\t');
     			getline(iss, entranceFee, '\t');

       			if(typeID == "1")
       				Attraction.insert(Attraction.getLength()+1, new Sport(atoi(ID.c_str()), name, atoi(typeID.c_str()), address, number, operatingHour));
       			else if(typeID == "2")
       				Attraction.insert(Attraction.getLength()+1, new Culture(atoi(ID.c_str()), name, atoi(typeID.c_str()), address, number, operatingHour, atoi(entranceFee.c_str())));
       			else if(typeID == "3")
       				Attraction.insert(Attraction.getLength()+1, new Shopping(atoi(ID.c_str()), name, atoi(typeID.c_str()), address, number, operatingHour));
        	}
        	Cities.sortInsert(City(atoi(cityID.c_str()), cityName, Attraction));
        	Attraction.clear();
        }
    	loadFile.close();
    	if(!askName)
    		cout << "Load from " << filename << " success.\n";
    	return true;
 	}
 	else
 	{
		cout << "Error. Please make sure " << filename << " is with the same filder with this program.\n";
    	return false;
    }
}

bool saveFlight(string** flightArray, int newSize, bool askName)
{
	ofstream saveFlight;
	string filename;
	if(!askName)
	{
		cout << "Please enter a file name to save flight detail =>";
		getline(cin, filename);
	}
	else
		filename = "Flight.txt";
	saveFlight.open(filename);
	if(saveFlight.is_open())
	{
		saveFlight << "City:\t";
		saveFlight << newSize << '\n';
		for(int j=0; j<newSize; j++)
		{
			saveFlight << "City" << j+1 << ":\t" << flightArray[0][j] << '\n';
		}
		saveFlight << '\n';
		for(int j=0; j<newSize-1; j++)
			saveFlight << "City" << j+1 << '\t';
		saveFlight << "City" << newSize << '\n';
		for(int i=1; i<newSize+1; i++)
		{
			for(int j=0; j<newSize-1; j++)
				saveFlight << flightArray[i][j] << '\t';
			saveFlight << flightArray[i][newSize-1] << '\n';
		}
		saveFlight.close();
		if(!askName)
			cout << "Save to " << filename << " success.\n";
		return true;
	}
	else
		return false;
}

bool loadFlight(string**& flightArray, int& size, bool askName)
{
	ifstream loadFlight;
	string filename, record, detail, input;
	int cityNumber;
	if(!askName)
	{
		cout << "Please enter a file name to load flight detail =>";
		getline(cin, filename);
	}
	else
		filename = "Flight.txt";
	loadFlight.open(filename);
	if(loadFlight.good())
	{
		while(getline(loadFlight, record, '\n'))
		{
			istringstream iss(record);
			getline(iss, input, '\t');
			getline(iss, input, '\t');    //To get the number of city
			cityNumber = convertStringToInt(input);
			if(cityNumber == 0)     //To check is it empty
				break;
			size = cityNumber;
			flightArray = new string*[size+1];
			for(int i=0; i<size+1; i++)     //Row has 1 more extra than column
				flightArray[i] = new string[size];
			for(int j=0; j<size; j++)
			{
				getline(loadFlight, record, '\n');
				istringstream iss2(record);
				getline(iss2, detail, '\t');
				getline(iss2, detail, '\t');
				flightArray[0][j] = detail;
			}

			getline(loadFlight, record, '\n');     //To discard the empty line
			getline(loadFlight, record, '\n');     //To discard the city1 to n size of city
			for(int i=1; i<size+1; i++)     //Row has 1 more extra than column
			{
				getline(loadFlight, record, '\n');
				istringstream iss3(record);
				for(int j=0; j<size; j++)
				{
					getline(iss3, detail, '\t');
					flightArray[i][j] = detail;
				}
			}
		}
		loadFlight.close();
		if(!askName)
			cout << "Load from " << filename << " success.\n";
		return true;
	}
	else
	{
		cout << "Error. Please make sure " << filename << " is with the same filder with this program.\n";
		return false;
	}
}

bool savePass(string password)
{
	ofstream savePass;
	savePass.open("Password.txt");
	if(savePass.good())
	{
		savePass << "Password:\t";
		savePass << password;
		savePass.close();
		return true;
	}
	else
		return false;
}

bool loadPass(string& password)
{
	ifstream loadPass;
	string record, input;
	loadPass.open("Password.txt");
	if(loadPass.good())
	{
		getline(loadPass, record, '\n');
		istringstream iss(record);
		getline(iss, input, '\t');
		getline(iss, input, '\t');
		password = input;
		loadPass.close();
		return true;
	}
	else
		return false;
}

void changePass(string& password)
{
	string oldPass, newPass1, newPass2;
	if(loadPass(password))
	{
		bool errorChecking = false;
		while(!errorChecking)
		{
			system("cls");
			cout << "\nPlease key in the old password => ";
			getline(cin, oldPass);
			if(oldPass == password)
			{
				errorChecking = false;
				while(!errorChecking)
				{
					system("cls");
					cout << "\nPlease enter the new password => ";
					getline(cin, newPass1);
					cout << "\nPlease retype the new password => ";
					getline(cin, newPass2);
					if(newPass1 != newPass2)
					{
						cout << "\nThe password does not match. Please enter again.\n";
						system("pause");
					}
					else
					{
						savePass(newPass2);
						cout << "\nPassword successfully changed.\n";
						errorChecking = true;
					}
				}
			}
			else
			{
				cout << "\nThe password does not match. Please enter again.\n";
				system("pause");
			}
		}
	}
	else
	{
		cout << "Error loading from Password.txt. Please make sure Password.txt is with the same folder as this program.\n";
		system("pause");
		system("cls");
	}
}

bool adminLogin(string& password)
{
	password = "";
	string pass = "";
	char ch;
	if(loadPass(pass))
	{
		system("cls");
		cout << "\nPlease enter password to login as administator => ";
		ch = _getch();
		while(ch != 13)     //13 is enter key in ascii
		{
			password.push_back(ch);
			cout << '*';
			ch = _getch();
		}
		if(password == pass)
		{
			cout << "\nAccess granted. Welcome administrator!\n";
			system("pause");
			return true;
		}
		else
		{
			cout << "\nAccess denied. Please retype your password.\n";
			system("pause");
			return false;
		}
	}
	else
	{
		cout << "\nPlease make sure Password.txt is in the same folder with this program.\n";
		cout << "Change password failed.\n";
		system("pause");
		return false;
	}
}

void addDirectFlight(string**& flightArray, int size, LinkedList<City>& Cities, string cityName, int cityID, bool askName)
{
	bool continueDirect = false, errorChecking, directTo = false;
	string input;
	int cityDirect;
	while(!continueDirect)
	{
		errorChecking = false;
		while(!errorChecking)
		{
			system("cls");
			cout << endl;
			for(int i=1; i<Cities.getLength()+1; i++)
				if(Cities[i].getName() != cityName)     //To make sure user cant add direct flight to the city itself
					Cities[i].display();
			if(!directTo)
				cout << "\nDoes " << cityName << " have any direct flight to any city above? N to stop.\n";
			else
				cout << "\nDoes any city above have direct flight to " << cityName << "? N to stop.\n";
			cout << "Please enter the city id => ";
			getline(cin, input);
			if(input == "n" || input == "N")
			{
				if(!directTo)
					directTo = true;
				else
					continueDirect = true;
				break;
			}
			cityDirect = convertStringToInt(input);
			for(int i=1; i<size+1; i++)
				if(Cities[i].getID() == cityDirect && cityDirect != cityID)
				{
					errorChecking = true;
					break;
				}
			if(!errorChecking)
			{
				cout << "Error. Invalid input." << endl;
				cout << "Please enter an valid city ID." << endl;
				system("pause");
			}
		}
		
		for(int i=1; i<size+1; i++)
			for(int j=0; j<size; j++)
				if(Cities[i].getID() == cityDirect && Cities[j+1].getName() == cityName)
				{
					if(!directTo)
						flightArray[j+1][i-1] = "1";
					else
						flightArray[i][j] = "1";
				}
		saveFlight(flightArray, size, askName);
	}
}

void removeDirectFlight(string**& flightArray, int size, LinkedList<City>& Cities, string cityName, int cityID, bool askName)
{
	bool continueDirect = false, errorChecking, directTo = false;
	string input;
	int cityDirect;
	while(!continueDirect)
	{
		errorChecking = false;
		while(!errorChecking)
		{
			system("cls");
			cout << endl;
			for(int i=1; i<Cities.getLength()+1; i++)
				if(Cities[i].getName() != cityName)     //To make sure user cant add direct flight to the city itself
					Cities[i].display();
			if(!directTo)
				cout << "\nDoes " << cityName << " do not have direct flight to any city above? N to stop.\n";
			else
				cout << "\nAny city above do not have direct flight to " << cityName << "? N to stop.\n";
			cout << "Please enter the city id => ";
			getline(cin, input);
			if(input == "n" || input == "N")
			{
				if(!directTo)
					directTo = true;
				else
					continueDirect = true;
				break;
			}
			cityDirect = convertStringToInt(input);
			for(int i=1; i<size+1; i++)
				if(Cities[i].getID() == cityDirect && cityDirect != cityID)
				{
					errorChecking = true;
					break;
				}
			if(!errorChecking)
			{
				cout << "Error. Invalid input." << endl;
				cout << "Please enter an valid city ID." << endl;
				system("pause");
			}
		}
		
		for(int i=1; i<size+1; i++)
			for(int j=0; j<size; j++)
				if(Cities[i].getID() == cityDirect && Cities[j+1].getName() == cityName)
				{
					if(!directTo)
						flightArray[j+1][i-1] = "0";
					else
						flightArray[i][j] = "0";
				}
		saveFlight(flightArray, size, askName);
	}
}

void displayCityIDName(LinkedList<City>& Cities)
{
	cout << " ID\tName\n";
	for(int i=1; i<Cities.getLength()+1; i++)
		cout << " " << Cities[i].getID() << '\t' << Cities[i].getName() << endl;
	cout << "\nPlease enter ID to continue =>";
}

int getCityID(LinkedList<City>& Cities, int adminAccess)
{
	bool errorChecking = false;
	int cityID;
	string input;
	while(!errorChecking)     //To make sure user enter valid range when choosing city
	{
		if(adminAccess == 1 || adminAccess == 4 || adminAccess == 7)     //Modify
			cout << "\nWhich city to modify?\n\n";
		else if(adminAccess == 5 || adminAccess == 8)     //Add
			cout << "\nAdd to which city?\n\n";
		else if(adminAccess == 6 || adminAccess == 9)     //Remove
			cout << "\nRemove from which city?\n\n";
		displayCityIDName(Cities);
		getline(cin, input);
		cityID = convertStringToInt(input);
		cout << endl;
		for(int i=1; i<Cities.getLength()+1; i++)
		{
			if(cityID == Cities[i].getID())
			{
				errorChecking = true;
				break;
			}
		}
		if(!errorChecking)
		{
			cout << "Error. Invalid input." << endl;
			cout << "Please enter an valid city ID." << endl;
			system("pause");
			system("cls");
		}
	}
	return cityID;
}

int getCityPosition(LinkedList<City>& Cities, int cityID)
{
	for(int i=1; i<Cities.getLength()+1; i++)
		if(cityID == Cities[i].getID())
			return i;     //To get which position the city is in
}

string getCityName(LinkedList<City>& Cities, int cityID)
{
	for(int i=1; i<Cities.getLength()+1; i++)
		if(cityID == Cities[i].getID())
			return Cities[i].getName();
}

int addOrRemoveAttOrCity(LinkedList<City>& Cities, int adminAccess, int cityID)
{
	string a, c, d, input;
	int b, cityPos, inputType, position;
	bool errorChecking;
	cityPos = getCityPosition(Cities, cityID);
	switch(adminAccess)
	{
		case 3:	a = "\n 1\tRemove front\n 2\tRemove back\n 3\tRemove from a position\n";
				b = Cities.getLength();
				c = "Which position to remove => ";
				d = "List of Cities\n\n";
				break;
		case 5:	a = "\n 1\tAdd front\n 2\tAdd back\n 3\tAdd to a position\n";
				b = Cities[cityPos].getAttractionLength()+1;
				c = "Which position to add => ";
				d = "List of Attractions\n\n";
				break;
		case 6:	a = "\n 1\tRemove front\n 2\tRemove back\n 3\tRemove from a position\n";
				b = Cities[cityPos].getAttractionLength();
				c = "Which position to remove => ";
				d = "List of Attractions\n\n";
				break;
	}

	errorChecking = false;
	while(!errorChecking)
	{
		cout << endl << d;
		for(int i=1; i<Cities.getLength()+1; i++)
		{
			if((adminAccess == 5 || adminAccess == 6) && (cityID == Cities[i].getID()))
				Cities[i].displayAttraction();
			else if(adminAccess == 3)
				Cities[i].display();
		}
		cout << a;
		cout << "\nPlease enter 1-3 to continue => ";
		getline(cin, input);
		inputType = convertStringToInt(input);
		if(inputType != 1 && inputType != 2 && inputType != 3)
		{
			cout << "\nError. Invalid input." << endl;
			cout << "Please enter 1-3 to continue." << endl;
			system("pause");
			system("cls");
		}
		else
			errorChecking = true;
	}
	if(inputType == 3)
	{
		errorChecking = false;
		while(!errorChecking)
		{
			cout << c;
			getline(cin, input);
			position = convertStringToInt(input);
			if(position == 1)
				inputType = 1;
			else if(position == b)
				inputType = 2;
			if(adminAccess == 3 || adminAccess == 6)
				if(position < 1 || position > b+1)     //To make sure the position did not go out of range
				{
					cout << "\nError. Invalid input." << endl;
					cout << "Please enter 1-" << b << "to continue." << endl;
					system("pause");
					system("cls");
				}
				else
					errorChecking = true;
			else if(adminAccess == 5)
				if(position < 1 || position > b+2)
				{
					cout << "\nError. Invalid input." << endl;
					cout << "Please enter 1-" << b+1 << " to continue." << endl;
					system("pause");
					system("cls");
				}
				else
					errorChecking = true;
		}
	}
	if(inputType == 1)
		position = 1;
	else if(inputType == 2)
		position = b;
	return position;
}

void checkContinue(int& inputAccess)
{
	bool errorChecking = false;
	string input;
	while(!errorChecking)
	{
		cout << "\nDo you want to continue?" << endl;
		cout << "Please enter Y to continue, N to return main menu => ";
		getline(cin, input);
		if(input == "y" || input == "Y")
		{
			inputAccess = 1;     //To return to the tourist information system menu
			errorChecking = true;     //To exit the error checking loop
			system("cls");
		}
		else if(input == "n" || input == "N")
		{
			inputAccess = 0;     //To return to main menu
			errorChecking = true;     //To exit the error checking loop
			system("cls");
		}
		else
		{
			cout << "\nError. Invalid input." << endl;
			cout << "Please enter Y or N to continue." << endl;
			system("pause");
		}
	}
}

void removeFlight(string**& flightArray, int& size, int position, bool askName, LinkedList<City>& Cities)
{
	if(position == 1)     //To remove the front detail
	{
		for(int i=2; i<size+1; i++)     //Shifting the detail of flight to the top left
			for(int j=1; j<size; j++)
				flightArray[i-1][j-1] = flightArray[i][j];
		for(int j=1; j<size; j++)     //Shifting the city name to the left
			flightArray[0][j-1] = flightArray[0][j];
	}
	else if(position != Cities.getLength())     //To remove any detail user specify
	{
		for(int i=0; i<position; i++)     //Shifting the right side column to the user entered position
			for(int j=position; j<size; j++)
				flightArray[i][j-1] = flightArray[i][j];
		for(int i=position+1; i<size+1; i++)     //Shifting the bottom side row to the user entered position
			for(int j=0; j<position-1; j++)
				flightArray[i-1][j] = flightArray[i][j];
		for(int i=position+1; i<size+1; i++)     //Shifting the detail of flight to the bottom right
			for(int j=position; j<size; j++)
				flightArray[i-1][j-1] = flightArray[i][j];
	}

	int newSize = size - 1;     //To increase the size by 1 after insert a new city
	string **tempFlightArray = new string*[newSize+1];
	for(int i=0; i<newSize+1; i++)
		tempFlightArray[i] = new string[newSize];
	for(int i=0; i<size; i++)
		for(int j=0; j<size-1; j++)
			tempFlightArray[i][j] = flightArray[i][j];
	for(int i=0; i<size; i++)     //To delete the old array
		delete [] flightArray[i];
	delete [] flightArray;
	flightArray = tempFlightArray;
	saveFlight(flightArray, newSize, askName);
	size = newSize;
}

void addFlight(string**& flightArray, int& size, int position, string cityName)
{
	int newSize = size + 1;     //To increase the size by 1 after insert a new city
	string **tempFlightArray = new string*[newSize+1];
	for(int i=0; i<newSize+1; i++)
		tempFlightArray[i] = new string[newSize];
	for(int i=0; i<size+1; i++)     //To copy old array to new array
		for(int j=0; j<size; j++)
			tempFlightArray[i][j] = flightArray[i][j];
	for(int i=0; i<size; i++)     //To delete the old array
		delete [] flightArray[i];
	delete [] flightArray;
	flightArray = tempFlightArray;

	for(int i=1; i<position; i++)     //Shifting the right side column from the user entered position
		for(int j=newSize-2; j>position-2; j--)
			flightArray[i][j+1] = flightArray[i][j];
	for(int i=newSize-1; i>position-1; i--)     //Shifting the bottom side row from the user entered position
		for(int j=0; j<position-1; j++)
			flightArray[i+1][j] = flightArray[i][j];
	for(int i=newSize-1; i>position-1; i--)     //Shifting the detail of flight to the bottom right
		for(int j=newSize-2; j>position-2; j--)
			flightArray[i+1][j+1] = flightArray[i][j];
	for(int i=1; i<newSize+1; i++)     //To set the column to 0
		flightArray[i][position-1] = "0";
	for(int j=0; j<newSize; j++)     //To set the row to 0
		flightArray[position][j] = "0";
	for(int j=newSize-2; j>position-2; j--)     //Shifting the city name to the right
		flightArray[0][j+1] = flightArray[0][j];
	flightArray[0][position-1] = cityName;
	size = newSize;
}

bool checkCityEmpty(LinkedList<City>& Cities)
{
	if(Cities.isEmpty())     //To check Cities list is empty or not
	{
		cout << "\nThere is no city inside Name.txt.\n";
		return true;
	}
	else
		return false;
}


int main()
{
	string **flightArray, input, cityName, data, record, password, name, address, number, operatingHour, cityNameA, cityNameB;
	int adminAccess = 0, inputAccess = 0, subAccess, size, cityID, cityPos, position, ID, entranceFee, typeID, attractionID, cityA, cityB, cityPosA, cityPosB, oldPos;
	bool askName = true, errorChecking, menuLoop;
	LinkedList<Attraction*> Attraction;
	LinkedList<City> Cities;
	LinkedList<string> indirectFlight;
	ofstream savefile;
    ifstream loadfile;
    
	while(inputAccess == 0)     //To loop back the whole program
	{
		while(!loadFile(Cities, Attraction, askName))     //To load the attraction and city
		{
			cout << "Please make sure Name.txt is in the same folder with this program before proceeding.\n";
			system("pause");
			system("cls");
		}
		while(!loadFlight(flightArray, size, askName))     //To load the flight data
		{
			cout << "Please make sure Flight.txt is in the same folder with this program before proceeding.\n";
			system("pause");
			system("cls");
		}
		system("cls");
		cout << "+------------------------------------------------+\n";
		cout << "|                                                |\n";
		cout << "|           Tourist Information System           |\n";
		cout << "|                                                |\n";
		cout << "+------------------------------------------------+\n\n";
		
		cout << " 1\tTourist Information System\n";
		cout << " 2\tAdministator login\n";
		cout << " 3\tQuit\n\n";
		cout << "Please enter 1-3 to continue => ";
		getline(cin, input);
		inputAccess = convertStringToInt(input);
		if(inputAccess < 1 || inputAccess > 3)     //1,2,3 is to check is it in the range
		{
			cout << "\nError. Invalid input.\n";
			cout << "Please enter 1-3 to access the system.\n";
			inputAccess = 0;
			system("pause");
			system("cls");
		}

		if(inputAccess == 3)     //To quit the program
			return 0;

		while(inputAccess == 1)     //To access tourist system
		{
			if(checkCityEmpty(Cities))     //If no city, it will auto go back to main menu
			{
				inputAccess = 0;
				system("pause");
				system("cls");
				break;
			}

			errorChecking = false;
			while(!errorChecking)     //To make sure user enter 1 or 2 to continue
			{
				system("cls");
				cout << "\nTourist Information System\n\n";
				cout << " 1\tTo access attraction detail\n";
				cout << " 2\tTo access flight information\n\n";
				cout << "Please enter 1-2 to continue => ";
				getline(cin, input);
				subAccess = convertStringToInt(input);
				system("cls");
				if(subAccess < 1 || subAccess > 2)
				{
					cout << "\nError. Invalid input.\n";
					cout << "Please enter 1-2 to continue.\n";
					system("pause");
					system("cls");
				}
				else
					errorChecking = true;
			}

			if(subAccess == 1)     //To access attraction detail
			{
				cout << "\nCity ID and Name\n\n";
				cityID = getCityID(Cities, adminAccess);     //To get the city ID
				cityPos = getCityPosition(Cities, cityID);
				system("cls");
				if(Cities[cityPos].getAttractionEmpty())
					cout << "\nAttraction Detail\n\n" << Cities[cityPos].getName() << " have no attraction.\n";
				else
				{
					errorChecking = false;
					while(!errorChecking)     //To make sure user enter only 1-4 for type id
					{
						cout <<"\nType of attraction\n\n";
						cout << " 1\tSport\n";
						cout << " 2\tCulture\n";
						cout << " 3\tShopping\n";
						cout << " 4\tShow All\n";
						cout << "\nPlease enter 1-4 to access attractions => ";
						getline(cin, input);
						typeID = convertStringToInt(input);
						system("cls");
						if(typeID < 1 || typeID > 4)
						{
							cout << "\nError. Invalid input.\n";
							cout << "Please enter 1-4 to access attractions.\n";
							system("pause");
							system("cls");
						}
						else
							errorChecking = true;     //To exit the error checking loop
					}
					errorChecking = false;
					while(!errorChecking)
					{
						cout << "\nList of Attractions\n\n";
						if (typeID == 4)
							Cities[cityPos].displayAttraction();     // To show all of the attractions in a city
						else
							Cities[cityPos].displayAttractionTypeID(typeID);     // To show type id that user specify in a city
						cout << endl;
						cout << "Enter the ID you want to access => ";
						getline(cin, input);
						attractionID = convertStringToInt(input);
						system("cls");
						for(int i=1; i<Cities[cityPos].getAttractionLength()+1; i++)
						{
							if(attractionID == Cities[cityPos].getAttractionID(i))
								errorChecking = true;     //To exit the error checking loop
						}
						if(!errorChecking)
						{
							cout << "\nError. Invalid input.\n";
							cout << "Please enter the ID shown to access the attraction.\n";
							system("pause");
						}
					}
					cout << "\nAttraction Detail\n\n";
					Cities[cityPos].displayAttractionDetail(attractionID);     // To show the detail that user choose
				}
				checkContinue(inputAccess);
			}
			else if(subAccess == 2)     //To access flight detail
			{
				errorChecking = false;
				while(!errorChecking)     //To make sure user enter valid range when choosing city A
				{
					cout << "\nCity ID and Name\n\n";
					cout << " ID\tName\n";
					for(int i=1; i<Cities.getLength()+1; i++)
						cout << " " << Cities[i].getID() << '\t' << Cities[i].getName() << endl;
					cout << "\nPlease enter the city ID for the following:\n";
					cout << "From which city => ";
					getline(cin, input);
					cityA = convertStringToInt(input);
					cout << endl;
					system("cls");
					for(int i=1; i<Cities.getLength()+1; i++)
					{
						if(cityA == Cities[i].getID())
						{
							errorChecking = true;
							break;
						}
					}
					if(!errorChecking)
					{
						cout << "Error. Invalid input." << endl;
						cout << "Please enter an valid city ID." << endl;
						system("pause");
						system("cls");
					}
				}

				errorChecking = false;
				while(!errorChecking)     //To make sure user enter valid range when choosing city B
				{
					cout << "\nCity ID and Name\n\n";
					cout << " ID\tName\n";
					for(int i=1; i<Cities.getLength()+1; i++)
						if(cityA != Cities[i].getID())
							cout << " " << Cities[i].getID() << '\t' << Cities[i].getName() << endl;
					cout << "\nTo which city => ";
					getline(cin, input);
					cityB = convertStringToInt(input);
					cout << endl;
					system("cls");
					for(int i=1; i<Cities.getLength()+1; i++)
					{
						if(cityA == cityB)
							break;
						if(cityB == Cities[i].getID())
						{
							errorChecking = true;
							break;
						}
					}
					if(!errorChecking)
					{
						cout << "Error. Invalid input." << endl;
						cout << "Please enter an valid city ID." << endl;
						system("pause");
						system("cls");
					}
				}

				for(int i=1; i<Cities.getLength()+1; i++)     //To get the city name
				{
					if(cityA == Cities[i].getID())
						cityNameA = Cities[i].getName();
					if(cityB == Cities[i].getID())
						cityNameB = Cities[i].getName();
				}

				cityPosA = getCityPosition(Cities, cityA);     //To get the position of city A
				cityPosB = getCityPosition(Cities, cityB);     //To get the position of city B

				cout << "\nFlight Detail\n\n";
				if(flightArray[cityPosA][cityPosB-1] == "1")     //To check for direct flight
					cout << "There is direct flight from "<< cityNameA << " to " << cityNameB << ".\n";
				else     //To check for indirect flight if there is no direct flight
				{
					indirectFlight.clear();     //To clear the list of the indirect flight
					Flight f(size);     //To initialise how many vertices as the number of city
					for(int i=1; i<size+1; i++)     //To add all available direct flight to the stack
						for(int j=0; j<size; j++)
							if(flightArray[i][j] == "1")
								f.addEdge(i-1, j);

					if(f.isReachable(cityPosA-1, cityPosB-1))     //To see is the city A connected to city B
					{
						cout<< "There is indirect flight from " << cityNameA << " to " << cityNameB << ".\n";
						while(!f.isEmptyStack())     //To cout all the connection of the indirect flight
						{
							for(int j = 0; j < size; j++)
								if(j == f.getStack())
								{
									indirectFlight.insert(indirectFlight.getLength()+1, flightArray[0][j]);
									f.removeStack();
									break;
								}
						}
						for(int i = indirectFlight.getLength(); i > 1; i--)
							cout << indirectFlight[i] << " -> ";
						cout << indirectFlight[1] << "\n";
					}
					else
						cout<< "There is no direct and indirect flight from " << cityNameA << " to " << cityNameB << ".\n";
				}
				checkContinue(inputAccess);
			}
		}

		if(inputAccess == 2)     //To access the administrator main menu
		{
			errorChecking = false;
			while(!errorChecking)     //To check does admin key in correct password
				errorChecking = adminLogin(password);
			menuLoop = false;
			while(!menuLoop)     //To keep loop inside administrator menu until user back to main menu
			{
				if(adminAccess >= 1 && adminAccess <= 9)     //To auto load the program if the user inputed 1-6
				{
					if(loadFile(Cities, Attraction, askName) && loadFlight(flightArray, size, askName))
					{
			        	if(adminAccess == 1 || adminAccess == 4 || adminAccess == 7)
			        		cout << "\nModify success!\n";
			        	else if(adminAccess == 2 || adminAccess == 5 || adminAccess == 8)
			        		cout << "\nAdd success!\n";
			        	else if(adminAccess == 3 || adminAccess == 6 || adminAccess == 9)
			        		cout << "\nRemove success!\n";
			        }
			        else
			        	cout << "Error.\n";
			        system("pause");
		        }
		        if(adminAccess == 11 && !errorChecking)     //If admin load fail, it will auto load from Name.txt and Flight.txt
		        {
		        	askName = true;
		        	loadFile(Cities, Attraction, askName);
		        	loadFlight(flightArray, size, askName);
		        }

		     	adminAccess = 0;
		     	while(adminAccess == 0)     //To access default main menu
		     	{
		     		system("cls");
					cout << "\nAdministrator Menu\n\n";
					cout << " 1\tModify existing city data\n";
					cout << " 2\tAdd new city data\n";
					cout << " 3\tRemove existing city data\n";
					cout << " 4\tModify existing attraction data\n";
					cout << " 5\tAdd new attraction data\n";
					cout << " 6\tRemove existing attraction data\n";
					cout << " 7\tModify existing flight data\n";
					cout << " 8\tAdd new flight data\n";
					cout << " 9\tRemove existing flight data\n";
					cout << " 10\tSave to text file\n";
					cout << " 11\tLoad from text file\n";
					cout << " 12\tTo view all cities\n";
					cout << " 13\tTo view all attractions\n";
					cout << " 14\tTo view all direct flights\n";
					cout << " 15\tTo change administator password\n";
					cout << " 16\tBack to main menu\n";
					cout << "\nPlease enter 1-16 to continue => ";
					getline(cin, input);
					adminAccess = convertStringToInt(input);
					if(adminAccess < 1 || adminAccess > 16)
					{
						cout << "\nError. Invalid input.\n";
						cout << "Please enter 1-13 to continue.\n";
						system("pause");
						adminAccess = 0;
					}
				}
				if(adminAccess == 1)     //To modify city
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						errorChecking = false;
						ID = getCityID(Cities, adminAccess);
						system("cls");

						name = getCityName(Cities, ID);     //To get the name of the the id that user entered
						
						errorChecking = false;
						while(!errorChecking)     //To check new attraction id will be unique or not
						{
							cout << "\nPlease update the following data :\n";
							cout << "\nID => ";
							getline(cin, input);
							cityID = convertStringToInt(input);
							if(cityID != 0)
							{
								if(cityID != ID)     //If the new ID user entered is different from the id just now, the program will try to see whether the new ID is unique or not
								{
									for(int i=1; i<Cities.getLength()+1; i++)
									{
										errorChecking = true;     //To make it default always will exit error checking loop
										if(cityID == Cities[i].getID())
										{
											errorChecking = false;     //If the ID is not unique, it will change from true to false and will stuck in the error checking loop
											break;
										}

									}
									if(!errorChecking)
									{
										cout << "Error. Invalid input." << endl;
										cout << "Please enter the original city ID or unique city ID." << endl;
										system("pause");
										system("cls");
									}
								}
								else
									errorChecking = true;
							}
							if(!errorChecking)
							{
								cout << "Error. Invalid input.\n";
								cout << "You cannot input 0 as city ID.\n";
								system("pause");
								system("cls");
							}
						}
						errorChecking = false;
						while(!errorChecking)     //To check new attraction name will be unique or not
						{
							cout << "\nName => ";
							getline(cin, cityName);
							if(!cityName.empty())
							{
								if(cityName != name)     //If the new name user entered is different from the name just now, the program will try to see whether the new name is unique or not
								{
									for(int i=1; i<Cities.getLength()+1; i++)
									{
										errorChecking = true;     //To exit the error checking loop
										if(cityName == Cities[i].getName())
										{
											errorChecking = false;
											break;
										}
									}
									if(!errorChecking)
									{
										cout << "Error. Invalid input." << endl;
										cout << "Please enter the original city name or unique city name." << endl;
										system("pause");
										system("cls");
									}
								}
								else
									errorChecking = true;
							}
							if(!errorChecking)
							{
								cout << "Error. Invalid input.\n";
								cout << "You cannot input empty string.\n";
								system("pause");
								system("cls");
							}
						}

						for(int i=1; i<Cities.getLength()+1; i++)
							if(Cities[i].getName() == name)
								oldPos = i;

						stringstream ss;
						ss << ID << '\t' << name;     //To combine the id and name that user entered
						record = ss.str();
						Attraction.clear();
						savefile.open("Temp.txt");
						loadfile.open("Name.txt");
						while(getline(loadfile, data))     //To detect the original line and replacement line is matched or not, if it not matched, it will save to the temp file. if it is matched, it will ignore that particular line that user wanted to remove
						{
							if(data == record)
							{
								savefile << cityID << '\t';
		     					savefile << cityName;
		     					savefile << '\n';
							}	
							else
								savefile << data << endl;
		     			}
						savefile.close();
						loadfile.close();
						remove("Name.txt");     //To delete the original file
						rename("Temp.txt", "Name.txt");     //To replace the original file with temp file
						loadFile(Cities, Attraction, askName);     //To load the modify file
						saveFile(Cities, askName);     //To save the sorted city to text file

						for(int i=1; i<Cities.getLength()+1; i++)
							if(Cities[i].getName() == cityName)
								position = i;

						removeFlight(flightArray, size, oldPos, askName, Cities);     //To remove the old city
						addFlight(flightArray, size, position, cityName);     //To add the new city
						saveFlight(flightArray, size, askName);
						addDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
					}
				}
				else if(adminAccess == 2)     //To add city
				{
					system("cls");
					errorChecking = false;
					while(!errorChecking)     //To make sure the city id user entered is unique
					{
						system("cls");
						cout << endl;
						for(int i=1; i<Cities.getLength()+1; i++)
							Cities[i].display();
						cout << "\nPlease enter the following things :" << endl;
						cout << "City ID => ";
						getline(cin, input);
						cityID = convertStringToInt(input);
						if(cityID != 0)
						{
							for(int i=1; i<Cities.getLength()+1; i++)     //To make sure user entered city id is not taken by other city
							{
								errorChecking = true;     //To exit the error checking loop
								if(cityID == Cities[i].getID() || cityID == 0)
								{
									errorChecking = false;
									break;
								}
							}
							if(!errorChecking)
							{
								cout << "Error. Invalid input." << endl;
								cout << "Please enter an ID that is not been taken yet." << endl;
								system("pause");
								system("cls");
							}
						}
						if(!errorChecking)
						{
							cout << "Error. Invalid input.\n";
							cout << "You cannot input 0 as city ID.\n";
							system("pause");
							system("cls");
						}
					}
					errorChecking = false;
					while(!errorChecking)     //To make sure the city name user entered is unique
					{
						cout << "City Name => ";
						getline(cin, cityName);
						if(!cityName.empty())     //To make sure the name user entered is not empty
						{
							for(int i=1; i<Cities.getLength()+1; i++)
							{
								errorChecking = true;     //To exit the error checking loop
								if(cityName == Cities[i].getName())
								{
									errorChecking = false;
									break;
								}
							}
							if(!errorChecking)
							{
								cout << "Error. Invalid input." << endl;
								cout << "Please enter a city name that is not been taken yet." << endl;
								system("pause");
								system("cls");
							}
						}
						if(!errorChecking)
						{
							cout << "Error. Invalid input.\n";
							cout << "You cannot input empty string.\n";
							system("pause");
							system("cls");
						}
					}

					Attraction.clear();
					Cities.sortInsert(City(cityID, cityName, Attraction));
					saveFile(Cities, askName);
					position = Cities.getCounter();     //To get the position of the newly inserted city
					addFlight(flightArray, size, position, cityName);
					addDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
				}
				else if(adminAccess == 3)     //To remove city
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						position = addOrRemoveAttOrCity(Cities, adminAccess, cityID);
						removeFlight(flightArray, size, position, askName, Cities);
						Cities.remove(position);
						saveFile(Cities, askName);
					}
				}
				else if(adminAccess == 4)     //To modify attraction data
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						cityID = getCityID(Cities, adminAccess);
						cityPos = getCityPosition(Cities, cityID);
						if(Cities[cityPos].getAttractionEmpty())
						{
							cout << "This city does not contain any attraction.\n";
							adminAccess = 0;     //To make sure it will not trigger the modify success! sentence
						}
						else
						{
							system("cls");
							errorChecking = false;
							while(!errorChecking)     //To check attraction id matches with attraction in the program
							{
								cout << "\nList of Attractions\n\n";
								for(int i=1; i<Cities.getLength()+1; i++)
									if(cityID == Cities[i].getID())
										Cities[i].displayAttraction();
								cout << "\nPlease enter ID to modify =>";
								getline(cin, input);
								attractionID = convertStringToInt(input);
								for(int i=1; i<Cities[cityPos].getAttractionLength()+1; i++)     //To make sure attraction user entered matches with attraction id in the program
								{
									if(attractionID == Cities[cityPos].getAttractionID(i))
									{
										errorChecking = true;
										break;
									}
								}
								if(!errorChecking)
								{
									cout << "\nError. Invalid input." << endl;
									cout << "Please enter an valid attraction ID." << endl;
									system("pause");
									system("cls");
								}
							}
							cout << "\nPlease update the following data :" << endl;
							errorChecking = false;
							while(!errorChecking)     //To check new attraction id will be unique or not
							{
								cout << "ID => ";
								getline(cin, input);
								ID = convertStringToInt(input);
								if(ID != attractionID)     //If the new ID user entered is different from the id just now, the program will try to see whether the new ID is unique or not
								{
									for(int i=1; i<Cities[cityPos].getAttractionLength()+1; i++)
									{
										errorChecking = true;     //To make it default always will exit error checking loop
										if(ID == Cities[cityPos].getAttractionID(i))
										{
											errorChecking = false;     //If the ID is not unique, it will change from true to false and will stuck in the error checking loop
											break;
										}
									}
								}
								else
									errorChecking = true;
							}
							cout << "\nName => ";
							getline(cin, name);

							errorChecking = false;
							while(!errorChecking)
							{
								cout<< "\nType ID => ";
								getline(cin, input);
								typeID = convertStringToInt(input);
								if(typeID != 1 && typeID != 2 && typeID != 3)
								{
									cout << "Error. Invalid input." << endl;
									cout << "Please enter 1-3 to continue." << endl;
									system("pause");
								}
								else
									errorChecking = true;
							}
							cout << "\nAddress => ";
							getline(cin, address);
							cout << "\nPhone number => ";
							getline(cin, number);
							cout << "\nOperating Hour => ";
							getline(cin, operatingHour);

							if(typeID == 2)
							{	
								cout << "\nEntrance Fee => ";
								getline(cin, input);
								entranceFee = convertStringToInt(input);
							}

							for(int i=1; i<Cities[cityPos].getAttractionLength()+1; i++)     //To combine all of the original information to one string for later detection
							{
								if(attractionID == Cities[cityPos].getAttractionID(i))     //To see whether the original information is typeID of 2(Culture), if it is then it will combine the entranceFee to the string too
								{
									stringstream ss;     //To combine multiple things to string
									if(Cities[cityPos].getAttractionTypeID(i) == 2)
									{
										Culture *culture = dynamic_cast<Culture*>(Cities[cityPos].getAttraction(i));
										ss << Cities[cityPos].getAttractionTypeID(i) << '\t' << Cities[cityPos].getAttractionID(i) << '\t' << Cities[cityPos].getAttractionName(i) << '\t' << Cities[cityPos].getAttractionAddress(i) << '\t' << Cities[cityPos].getAttractionNumber(i) << '\t' << Cities[cityPos].getAttractionOperatingHour(i) << '\t' << culture->getEntranceFee();
									}
									else
										ss << Cities[cityPos].getAttractionTypeID(i) << '\t' << Cities[cityPos].getAttractionID(i) << '\t' << Cities[cityPos].getAttractionName(i) << '\t' << Cities[cityPos].getAttractionAddress(i) << '\t' << Cities[cityPos].getAttractionNumber(i) << '\t' << Cities[cityPos].getAttractionOperatingHour(i);
									record = ss.str();
								}
							}
							loadfile.open("Name.txt");     //Original file
							savefile.open("Temp.txt");     //Temp file to modify and will replace original file afterwards
							while(getline(loadfile, data))     //To detect the original line and replacement line is matched or not, if it not matched, it will save to the temp file. if it is matched, it will ignore that particular line that user wanted to remove
							{
								if(data == record)
								{
									savefile << typeID << '\t';
			     					savefile << ID << '\t';
			     					savefile << name << '\t';
			     					savefile << address << '\t';
			     					savefile << number << '\t';
			     					savefile << operatingHour;
			     					if(typeID == 2)
			     						savefile << '\t' << entranceFee;
			     					savefile << '\n';
								}	
								else
								{
									savefile << data << endl;
			     				}
			     			}
							savefile.close();
							loadfile.close();
							remove("Name.txt");     //To delete the original file
							rename("Temp.txt", "Name.txt");     //To replace the original file with temp file
						}
					}
				}
				else if(adminAccess == 5)     //To add attraction data
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						cityID = getCityID(Cities, adminAccess);
						cityPos = getCityPosition(Cities, cityID);
						system("cls");
						position = addOrRemoveAttOrCity(Cities, adminAccess, cityID);
						errorChecking = false;
						while(!errorChecking)     //To make sure user entered 1-3 for choosing type of attraction
						{
							system("cls");
							cout << "\nType of attraction\n\n";
							cout << " 1\tSport" << endl;
							cout << " 2\tCulture" << endl;
							cout << " 3\tShopping" << endl;
							cout << "\nWhich type of attraction to add => ";
							getline(cin, input);
							typeID = convertStringToInt(input);
							if(typeID != 1 && typeID != 2 && typeID != 3)
							{
								cout << "\nError. Invalid input." << endl;
								cout << "Please enter 1-3 to continue." << endl;
								system("pause");
							}
							else
								errorChecking = true;
						}

						cout << "\nPlease enter the following things :" << endl;
						errorChecking = false;
						while(!errorChecking)     //To make sure the attraction ID that user entered is unique
						{
							cout << "ID => ";
							getline(cin, input);
							ID = convertStringToInt(input);
							if(Cities[cityPos].getAttractionEmpty())
								break;
							for(int i=1; i<Cities[cityPos].getAttractionLength()+1; i++)
							{
								errorChecking = true;     //To make it default always will exit error checking loop
								if(ID == Cities[cityPos].getAttractionID(i))
								{
									errorChecking = false;     //If the ID is not unique, it will change from true to false and will stuck in the error checking loop
									break;
								}
							}
						}
						cout << "\nName => ";
						getline(cin, name);
						cout << "\nAddress => ";
						getline(cin, address);
						cout << "\nPhone number => ";
						getline(cin, number);
						cout << "\nOperating Hour => ";
						getline(cin, operatingHour);
						if(typeID == 2)
						{
							cout << "\nEntrance Fee => ";
							getline(cin, input);
							entranceFee = convertStringToInt(input);     //If user enter any string it will auto change it to 0
						}
						savefile.open("Name.txt");
		             	if(savefile.is_open())
		             	{
		             		bool type1Insert = false, type2Insert = false;
		             		for(int i=1; i<Cities.getLength()+1; i++)
		             		{
								savefile << Cities[i].getID() << '\t'; //cout << Cities[i].getID() << endl;
		             			savefile << Cities[i].getName() << '\n';
		             			for(int j=1; j<Cities[i].getAttractionLength()+1; j++)
		             			{
		             				if(position == 1 && i == cityPos && !type1Insert)     //Add front
		             				{
		             					savefile << typeID << '\t';
		             					savefile << ID << '\t';
		             					savefile << name << '\t';
		             					savefile << address << '\t';
		             					savefile << number << '\t';
		             					savefile << operatingHour;
		             					if(typeID == 2)
		             						savefile << '\t' << entranceFee;
		             					savefile << '\n';
		             					type1Insert = true;
		             				}
		             				if(position != 1 && position != Cities[i].getAttractionLength()+1 && j == position && i == cityPos)
		             				{
		             					savefile << typeID << '\t';
		             					savefile << ID << '\t';
		             					savefile << name << '\t';
		             					savefile << address << '\t';
		             					savefile << number << '\t';
		             					savefile << operatingHour;
		             					if(typeID == 2)
		             						savefile << '\t' << entranceFee;
		             					savefile << '\n';
		             				}
		             				savefile << Cities[i].getAttractionTypeID(j) << '\t';
		             				savefile << Cities[i].getAttractionID(j) << '\t';
		             				savefile << Cities[i].getAttractionName(j) << '\t';
		             				savefile << Cities[i].getAttractionAddress(j) << '\t';
		             				savefile << Cities[i].getAttractionNumber(j) << '\t';
		             				savefile << Cities[i].getAttractionOperatingHour(j);
		             				if(Cities[i].getAttractionTypeID(j) == 2)
		             				{
		             					Culture *culture = dynamic_cast<Culture*>(Cities[i].getAttraction(j));
		             					savefile << '\t' << culture->getEntranceFee();
		             				}
		             				savefile << '\n';
		             			}
		             			if(position == Cities[i].getAttractionLength()+1 && i == cityPos && !type2Insert)
		         				{
		         					savefile << typeID << '\t';
		         					savefile << ID << '\t';
		         					savefile << name << '\t';
		         					savefile << address << '\t';
		         					savefile << number << '\t';
		         					savefile << operatingHour;
		         					if(typeID == 2)
		         						savefile << '\t' << entranceFee;
		         					savefile << '\n';
		         					type2Insert = true;
		         				}
		             			savefile << '\n';
		             		}
		                	savefile.close();
		             	}
		             	else
		           			cout << "Error." << endl;
		           	}
				}
				else if(adminAccess == 6)     //To remove attraction data
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						cityID = getCityID(Cities, adminAccess);
						cityPos = getCityPosition(Cities, cityID);
						if(Cities[cityPos].getAttractionEmpty())
						{
							cout << "This city does not contain any attraction.\n";
							adminAccess = 0;     //To make sure it will not trigger the remove success! sentence
						}
						else
						{
							system("cls");
							position = addOrRemoveAttOrCity(Cities, adminAccess, cityID);
							stringstream ss;     //To combine multiple things to strings
							if(Cities[cityPos].getAttractionTypeID(position) == 2)
							{
								Culture *culture = dynamic_cast<Culture*>(Cities[cityPos].getAttraction(position));
			 					entranceFee = culture->getEntranceFee();
			 					ss << Cities[cityPos].getAttractionTypeID(position) << '\t' << Cities[cityPos].getAttractionID(position) << '\t' << Cities[cityPos].getAttractionName(position) << '\t' << Cities[cityPos].getAttractionAddress(position) << '\t' << Cities[cityPos].getAttractionNumber(position) << '\t' << Cities[cityPos].getAttractionOperatingHour(position) << '\t' << entranceFee;
							}
							else
								ss << Cities[cityPos].getAttractionTypeID(position) << '\t' << Cities[cityPos].getAttractionID(position) << '\t' << Cities[cityPos].getAttractionName(position) << '\t' << Cities[cityPos].getAttractionAddress(position) << '\t' << Cities[cityPos].getAttractionNumber(position) << '\t' << Cities[cityPos].getAttractionOperatingHour(position);
							record = ss.str();
							loadfile.open("Name.txt");
							savefile.open("Temp.txt");
							while(getline(loadfile, data))
								if(data != record)
									savefile << data << endl;
							savefile.close();
							loadfile.close();
							remove("Name.txt");
							rename("Temp.txt", "Name.txt");
						}
					}
				}
				else if(adminAccess == 7)     //To modify flight data
				{
					system("cls");
					cityID = getCityID(Cities, adminAccess);
					cityName = getCityName(Cities, cityID);
					addDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
					removeDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
				}
				else if(adminAccess == 8)     //To add flight data
				{
					system("cls");
					cityID = getCityID(Cities, adminAccess);
					cityName = getCityName(Cities, cityID);
					addDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
				}
				else if(adminAccess == 9)     //To remove flight data
				{
					system("cls");
					cityID = getCityID(Cities, adminAccess);
					cityName = getCityName(Cities, cityID);
					removeDirectFlight(flightArray, size, Cities, cityName, cityID, askName);
				}
				else if(adminAccess == 10)     //To save to text file
				{
					if(!checkCityEmpty(Cities))
					{
						system("cls");
						cout << endl;
						askName = false;
		            	if(saveFile(Cities, askName))
		            		saveFlight(flightArray, size, askName);
						askName = true;
					}
				}
				else if(adminAccess == 11)     //To load from text file
				{
					system("cls");
					cout << endl;
					askName = false;     //To make sure it will ask user to enter the file name to the program
					errorChecking = false;
					if(loadFile(Cities, Attraction, askName))
						if(loadFlight(flightArray, size, askName))
							errorChecking = true;
					askName = true;
				}
				else if(adminAccess == 12)     //To see all the cities
				{
					system("cls");
					cout << "\nList of Cities\n\n";
					if(!checkCityEmpty(Cities))
					{
						for(int i=1; i<Cities.getLength()+1; i++)
							Cities[i].display();
						cout << endl;
					}
				}
				else if(adminAccess == 13)     //To see all the attractions
				{
					system("cls");
					cout << "\nList of Attractions\n\n";
					if(!checkCityEmpty(Cities))
					{
						for(int i=1; i<Cities.getLength()+1; i++)
							Cities[i].displayAttraction();
						cout << endl;
					}
				}
				else if(adminAccess == 14)     //To see all direct flights
				{
					system("cls");
					if(!checkCityEmpty(Cities))
					{
						cout << "\nList of Direct Flights\n\n";
						for(int i=0; i<size+1; i++)
							for(int j=0; j<size; j++)
								if(flightArray[i][j] == "1")
									if(flightArray[0][j] == Cities[j+1].getName())
										cout << Cities[i].getName() << " -> " << Cities[j+1].getName() << '\n';
						cout << endl;
					}
				}
				else if(adminAccess == 15)     //To change administator password
					changePass(password);
				else if(adminAccess == 16)     //To get back the main menu
				{
					menuLoop = true;
					adminAccess = 0;
				}
				if(!menuLoop)     //If user choose to go back main menu, it will not show system("pause")
				{
					system("pause");
					system("cls");
				}
			}
			inputAccess = 0;     //To loop back the main menu
		}
	}
	return 0;
}