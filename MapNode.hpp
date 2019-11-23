#pragma once
/* Program		: MapNode.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Specialized node class definition for the injury nodes to be stored in the priority map
*/

#include <string>

class MapNode {
private:
	// Values
	int type = -1;
	int contagious = 1;
	int timeCriticality = 1;
public:
	std::string diagnosis; // Key
	// Constructor
	MapNode(std::string d, int t = -1, int s = 0, int tc = 0) : diagnosis(d), type(t), contagious(s), timeCriticality(tc) {}
	// Destructor
	~MapNode() { delete next; }
	// Getters and setters
	int getType();
	int getContagious();
	int getTimeCriticality();
	void setType(int t);
	void setContagious(int s);
	void setTimeCriticality(int tc);
	// Pointer to the next node
	MapNode* next = nullptr;
	// Overloaded Assignment operator
	void operator = (MapNode m);
};

