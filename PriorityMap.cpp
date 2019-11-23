/* Program		: PriorityMap.cpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Method definitions for the PriorityMap class
*/

#include <sstream>
#include "PriorityMap.hpp"

/* Method name	: PriorityMap Destructor
*  Accepts		: N/A
*  Returns		: N/A
*  Description	: Destroys the map and everything it stands for
*/
PriorityMap::~PriorityMap()
{
	if (head == nullptr)
		return;
	else {
		int i = 0;
		MapNode* del = head;
		MapNode* next = head->next;
		while (del != nullptr) {
			del->next = nullptr;
			delete del;
			if (next == nullptr)
				return;
			del = next;
			if (next->next != nullptr)
				next = next->next;
			else
				next = nullptr;
		}
	}
}

/* Method name	: addNode
*  Accepts		: string containing the name of the node
*  Returns		: void
*  Description	: adds a new node to the map
*/
void PriorityMap::addNode(std::string d)
{
	MapNode* value = new MapNode(d, -1, 1, 1);
	if (head == nullptr) {
		head = value;
		head->next = nullptr;
	}
	else
	{
		MapNode* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = value;
		curr = curr->next;
		curr = value;
		curr->next = nullptr;
	}
	this->size++;

}

/* Method name	: addNode (method overload)
*  Accepts		: string containing the name, int containing the type, int containing the contagiousness, int containing the time criticallity
*  Returns		: void
*  Description	: Adds a node to the map 
*/
void PriorityMap::addNode(std::string d, int t, int c, int tc)
{
	MapNode* value = new MapNode(d, t, c, tc);
	if (head == nullptr) {
		head = value;
	}
	else
	{
		MapNode* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = value;
		curr = curr->next;
		curr = value;
		curr->next = nullptr;
	}
	this->size++;

}

/* Method name	: printMap
*  Accepts		: nothing
*  Returns		: void
*  Description	: prints the contents of the map
*/
void PriorityMap::printMap()
{
	MapNode* cur = head;
	while (cur != nullptr) {
		std::cout << cur->diagnosis << std::endl;
		cur = cur->next;
	}
}

/* Method name	: to_string
*  Accepts		: nothing
*  Returns		: string
*  Description	: converts the contents of the map to a single string
*/
std::string PriorityMap::to_String()
{
	std::ostringstream os;
	MapNode* cur = head;
	while (cur != nullptr) {
		os << cur->diagnosis << "," << cur->getType() << "," << cur->getTimeCriticality() << "," << cur->getContagious() << std::endl;
		cur = cur->next;
	}
	return os.str();
}


// Gets map size
int PriorityMap::getSize()
{
	return size;
}

/* Method name	: operator [] overload
*  Accepts		: string containing the map key
*  Returns		: the node containing the value
*  Description	: Returns the node associated with the key
*/
MapNode* PriorityMap::operator[](std::string key)
{
	MapNode* curr = head;
	while (curr != nullptr && curr->diagnosis != key)
		curr = curr->next;
	// if the key is not in the map, create a node with that key
	if (curr == nullptr) {
		addNode(key);
		curr = head;
		while (curr != nullptr && curr->diagnosis != key)
			curr = curr->next;
	}
	return curr;
}

