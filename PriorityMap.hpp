#pragma once
/* Program		: PriorityMap.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Map that stores the specialized Map node class to be used in calculating priorities
*/

#include "MapNode.hpp"
#include <iostream>

class PriorityMap {
private:
	MapNode* head = nullptr;
	int size = 0;
public:
	// Constructor
	PriorityMap() {};
	// Destructor
	~PriorityMap();
	// Add node functions
	void addNode(std::string d);
	void addNode(std::string d, int t, int c, int tc);
	// Print method
	void printMap();
	// To string method
	std::string to_String();
	// Getters
	int getSize();
	// Index of operator [] overload
	MapNode* operator[] (std::string key);
};
