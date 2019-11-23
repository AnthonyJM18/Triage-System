#pragma once
/* Program		: Patient.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Patient class
*/

#include <string>
#include "LinkedList.hpp"
#include "Injury.hpp"


class Patient {
private:
	std::string * name;
	int* priority = nullptr;
	// Patients injury list
	LinkedList<Injury>* Ilist = new LinkedList<Injury>();
public:
	// constructors
	Patient(std::string n, int p = 0);
	Patient(Patient & p);
	// destructor
	~Patient();
	// Getters and setters
	int getPriority();
	void setPriority(int p);
	std::string getName();
	void setName(std::string* n);
	// Add a injury to the injury list
	void addToList(std::string injuryName , int type, int cont, int time, int sev);
	// traverse functions
	void traverseData();
	void printInjuries();
};