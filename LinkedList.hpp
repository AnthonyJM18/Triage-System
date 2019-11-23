#pragma once
/* Program		: LinkedList.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Templated Linked List class 
*/

#include <iostream>
#include "ListNode.hpp"

template<class T> class LinkedList
{
private:
	// Private member variables
	ListNode<T>* head = nullptr;
	ListNode<T>* tail = nullptr;
public:
	// 0-arg Constructor
	LinkedList<T>() {};

	// Destructor
	~LinkedList<T>();

	// Methods to add to the list
	void addTail(T* data);
	void addHead(T* data);

	// Methods to remove from the list
	void removeTail();
	void removeHead();

	// Method to traverse the list
	void traverse();

	// Method to get the size of the list
	unsigned getSize();

	// Methods to get/insert/delete data at a specific element
	ListNode<T>* getNode(unsigned ele);
	void insertAt(unsigned ele, T* data);
	void deleteAt(unsigned ele);
	
	// Method to swap two nodes
	void swapNodes(unsigned lhs, unsigned rhs);

};

/* Method name	: ~LinkedList()		|	Destructor
*  Accepts		: N/A
*  Returns		: N/A
*  Description	: Cleans up by deleting all nodes in the list (if any)
*/
template<class T>
LinkedList<T>::~LinkedList()
{
	// If the list is empty
	if (this->head == nullptr) {
		return;
	}
	// Node pointers to be used in the deleting of nodes
	ListNode<T>* delptr = nullptr;
	ListNode<T>* next = nullptr;
	delptr = this->head;
	next = delptr->next;
	// if the list has no elements return
	if (this->head == nullptr) { return; }
	// While there are nodes in the list, delete them.
	while (delptr != nullptr) {
		next = delptr->next;
		delete delptr;
		delptr = next;
	}
}

/* Method name	: addTail
*  Accepts		: Pointer to the templated type
*  Returns		: Void
*  Description	: Adds a node of templated type to the end/tail of the list
*/
template<class T>
void LinkedList<T>::addTail(T* data)
{
	// if list is empty add to head
	if (this->head == nullptr) {
		this->head = new ListNode<T>(data);
		this->head->previous = nullptr;
		this->tail = this->head;
		this->head->next = nullptr;
	}
	// else add it to the tail of the list
	else {
		ListNode<T>* tmp = new ListNode<T>(data);
		tmp->previous = this->tail;
		this->tail->next = tmp;
		this->tail = tmp;
		this->tail->next = nullptr;
	}
}

/* Method name	: addHead
*  Accepts		: Ponter to the templated type
*  Returns		: void
*  Description	: Adds a node to the front/head of the list
*/
template<class T>
void LinkedList<T>::addHead(T* data)
{
	// if the list is empty just add to the head
	if (this->head == nullptr) {
		this->head = new ListNode<T>(data);
		this->head->previous = nullptr;
		this->tail = this->head;
		this->head->next = nullptr;
	}
	// else add to the head and connect it to the rest of the list
	else {
		ListNode<T>* tmp = new ListNode<T>(data);
		tmp->previous = nullptr;
		tmp->next = head;
		head->previous = tmp;
		head = tmp;
	}
}

/* Method name	: removetail
*  Accepts		: Nothing
*  Returns		: void
*  Description	: Removes the tail of the list
*/
template<class T>
void LinkedList<T>::removeTail()
{
	// if list is empty exit function
	if (this->head == nullptr) {
		std::cout << "Nothing to remove" << std::endl;
		return;
	}
	// Check to see if the list only contains one element
	else if (this->head->next == nullptr) {
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
		return;
	}
	// if neither of the if statements is applicable, delete the tail and set the new tail
	ListNode<T>* tmp = this->tail->previous;
	delete this->tail;
	tail = tmp;
	tail->next = nullptr;
}

/* Method name	: removeHead
*  Accepts		: Nothing
*  Returns		: void
*  Description	: Remove the head of the list
*/
template<class T>
void LinkedList<T>::removeHead()
{
	// if list is empty exit function
	if (this->head == nullptr) {
		std::cout << "Nothing to remove" << std::endl;
		return;
	}
	// Check to see if the list only contains one element
	else if (this->head->next == nullptr) {
		delete this->head;
		this->head = nullptr;
		this->tail = nullptr;
		return;
	}
	// if neither of the if statements is applicable, delete the head and set the new head
	ListNode<T>* tmp = this->head->next;
	tmp->previous = nullptr;
	delete this->head;
	head = tmp;
}

/* Method name	: traverse
*  Accepts		: Nothing
*  Returns		: Void
*  Description	: Traverse the list by using the traverse method found in the templated type
*  IMPORTANT	: In order to use this function the Templated type must contain a method called traverseData() which will output the specified data
				  of your choosing 
*/
template<class T>
void LinkedList<T>::traverse()
{
	// if list is empty exit function
	if (this->head == nullptr) {
		return;
	}
	// Ptherwise traverse the list
	ListNode<T>* tmp = this->head;
	while (tmp != nullptr) {
		tmp->getData()->traverseData();
		tmp = tmp->next;
	}
}

/* Method name	: getSize
*  Accepts		: Nothing
*  Returns		: unsigned int
*  Description	: Gets the size of the list
*/
template<class T>
unsigned LinkedList<T>::getSize()
{
	unsigned i = 0;
	ListNode<T>* tmp = this->head;
	while (tmp != nullptr) {
		i++;
		tmp = tmp->next;
	}
	return i;
}

/* Method name	: getNode
*  Accepts		: unsinged integer representing the element the user wishes to get
*  Returns		: ListNode pointer of the templated type
*  Description	: Gets a specific node and returns it
*/
template<class T>
ListNode<T>* LinkedList<T>::getNode(unsigned ele)
{
	ListNode<T>* tmp = this->head;
	// Iterate through the list until the specified element is found
	for (unsigned i = 0; i < ele; i++) {
		tmp = tmp->next;
	}
	return tmp;
}

/* Method name	: insertAt
*  Accepts		: unsigned integer of the location you would like to insert to, and a pointer to the templated type
*  Returns		: void
*  Description	: inserts a node at the specified location
*/
template<class T>
void LinkedList<T>::insertAt(unsigned ele, T* data)
{
	if (ele >= this->getSize()) {
		this->addTail(data);
		return;
	}
	// set up node pointers to hold the address of the node currently at the position specified, and the element before it
	ListNode<T>* previousEle = nullptr;
	ListNode<T>* currEle = this->head;
	// Create the new node
	ListNode<T>* newEle = new ListNode<T>(data);
	// if the list only contains one element
	if (this->head->next == nullptr) {
		newEle->previous = nullptr;
		newEle->next = this->head;
		this->head->previous = newEle;
		this->tail = this->head;
		this->head = newEle;
		return;
	}
	if (currEle == nullptr) {
		addHead(data);
		return;
	}
	for (unsigned i = 0; i != ele; i++) {
		if (currEle == nullptr) {
			addTail(data);
			return;
		}
		currEle = currEle->next;
	}
	// if the element is the head insert at the head
	if (currEle == this->head) {
		this->addHead(data);
		return;
	}
	previousEle = currEle->previous;
	// insert the new node
	previousEle->next = newEle;
	currEle->previous = newEle;
	newEle->next = currEle;
	newEle->previous = previousEle;
}

/* Method name	: deleteAt
*  Accepts		: unsigned integer representing the node to be deleted
*  Returns		: void
*  Description	: Deletes the specified node
*/
template<class T>
void LinkedList<T>::deleteAt(unsigned ele)
{
	// Check to see if the list is empty
	if (this->head == nullptr) {
		std::cout << "Nothing to remove" << std::endl;
		return;
	}
	// Set up node pointer to hold the address of the entered element
	ListNode<T>* deleteEle = this->head;
	for (unsigned i = 0; i != ele; i++) {
		deleteEle = deleteEle->next;
	}
	// if the node to be deleted is the head
	if (deleteEle == this->head) {
		this->removeHead();
		return;
	}
	// if the node to be deleted is the tail
	else if (deleteEle == this->tail) {
		this->removeTail();
		return;
	}
	// Get the next and previous node and connect the two, isolating the node to be deleted
	ListNode<T>* nextEle = deleteEle->next;
	ListNode<T>* previousEle = deleteEle->previous;
	nextEle->previous = previousEle;
	previousEle->next = nextEle;
	// Delete the node
	delete deleteEle;
}

/* Method name	: swapNodes
*  Accepts		: two unsigned integers representing the index of the two nodes to swap
*  Returns		: void
*  Description	: Swaps two nodes
*/
template<class T>
void LinkedList<T>::swapNodes(unsigned lhs, unsigned rhs)
{
	ListNode<T>* temp = new ListNode<T>(new T(this->getNode(lhs)->getData()));
	T* rhsData = new T(getNode(rhs)->getData());
	T* lhsData = new T(getNode(lhs)->getData());
	this->deleteAt(lhs);
	this->insertAt(lhs, rhsData);
	this->insertAt(rhs, lhsData);
	this->deleteAt(rhs + 1);
}


