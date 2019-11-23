#pragma once
/* Program		: Injury.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Basic class that stores the name and calculated priority of the illness/injury 
				  Contains very basic functionality
*/

#include <string>

class Injury
{
private:
	std::string diagnosis;
	int priority = 0;
public:
	Injury* next = nullptr;
	Injury(std::string d, int s = 0) : diagnosis(d), priority(s) {}
	~Injury() { delete next;  }
	std::string getDiagnosis() { return diagnosis; }
	int getPriority() { return priority; }
	void setPriority(int s) { priority = s; }
};

