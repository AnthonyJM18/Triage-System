#pragma once
/* Program		: PriorityQueue.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Priority queue class
*/
#include "LinkedList.hpp"
#include "Patient.hpp"


class PriorityQueue
{
private:
	// LinkedLists to store patients. Stores both patiens in the queue, and the history of patients that have left the queue
	LinkedList<Patient>* queue = new LinkedList<Patient>();
	LinkedList<Patient>* history = new LinkedList<Patient>();
	// stores the number of elements in the queue
	unsigned num_Elements = 0;
public:
	// Default constructor
	PriorityQueue() {}
	// Destructor
	~PriorityQueue();
	// checks to see if the queue is empty
	bool isEmpty();
	// enqueue based of priority
	int priorityEnqueue(Patient* data);
	// dequeue a patient
	void dequeue();
	// peek at the next patient in the queue
	std::string peek();
	// print methods
	void printQueue();
	void printHistory();
	// bool to check if a patient is already in the queue
	bool is_in_queue(std::string name);
};

