/* Program		: Triage System.cpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: A hospital triage system that will keep track of all patients, there illnesses, and enqueue them based off there priority score
*/


#include "PriorityQueue.hpp"
#include <iostream>


/* Method name	: PriorityQueue destructor
*  Accepts		: N/A
*  Returns		: N/A
*  Description	: Thanos snaps his fingers and destroys the queue 
*/
PriorityQueue::~PriorityQueue(){
	delete queue;
	delete history;
}

/* Method name	: isEmpty
*  Accepts		: nothing
*  Returns		: bool
*  Description	: checks to see if the queue is empty
*/
bool PriorityQueue::isEmpty(){
	if (num_Elements == 0)
		return true;
	return false;
}

/* Method name	: priorityEnqueue
*  Accepts		: Patient data
*  Returns		: int containing the postition of the patient in the queue
*  Description	: Enqueues a patient in the list based off there priority
*/
int PriorityQueue::priorityEnqueue(Patient* data){
	// If there priority is less than 4 enqueue them to the end 
	if (data->getPriority() <= 4 || num_Elements == 0) {
		queue->addTail(data);
		num_Elements++;
		return queue->getSize() - 1;
	}
	// otherwise find the correct position in the queue and insert them
	ListNode<Patient>* tmp = queue->getNode(0);
	int index = 0;
	while (tmp->getData()->getPriority() >= data->getPriority() && tmp != nullptr) {
		tmp = tmp->next;
		if (tmp == nullptr) {
			queue->addTail(data);
			num_Elements++;
			return queue->getSize() - 1;
		}
		index++;
	}
	queue->insertAt((index), data);
	num_Elements++;
	return index;
}

/* Method name	: dequeue
*  Accepts		: nothing
*  Returns		: void
*  Description	: dequeues the patient with the highest priority / at the head of the queue
*/
void PriorityQueue::dequeue(){
	if (num_Elements > 0) {
		std::cout << queue->getNode(0)->getData()->getName() << " Moved to patient room" << std::endl;
		history->addTail(new Patient(*queue->getNode(0)->getData()));
		queue->removeHead();
		this->num_Elements--;
		if (num_Elements > 0)
			std::cout << "Next patient in queue " << peek() << " with priority " << queue->getNode(0)->getData()->getPriority() << std::endl;
	}
	else
		std::cout << "Nobody in queue" << std::endl;
}

/* Method name	: peek
*  Accepts		: nothing
*  Returns		: string
*  Description	: gets the name of the next patient to be dequeued
*/
std::string PriorityQueue::peek(){
	if (num_Elements > 0) 
		return queue->getNode(0)->getData()->getName();
	return "";
}

/* Method name	: printQueue
*  Accepts		: nothing
*  Returns		: void
*  Description	: Prints the contents of the queue
*/
void PriorityQueue::printQueue(){
	if (num_Elements > 0)
		queue->traverse();
	else
		std::cout << "Queue is empty" << std::endl;
}

/* Method name	: printHistory
*  Accepts		: nothing
*  Returns		: void
*  Description	: prints the history queue
*/
void PriorityQueue::printHistory(){
	if (history->getSize() > 0)
		history->traverse();
	else
		std::cout << "History is empty" << std::endl;
}

/* Method name	: is_in_queue
*  Accepts		: string representing the name of a patient
*  Returns		: bool
*  Description	: checks to see if the specified patient is in the queue
*/
bool PriorityQueue::is_in_queue(std::string name)
{
	for (unsigned i = 0; i < queue->getSize(); i++) {
		if (queue->getNode(i)->getData()->getName() == name) {
			return true;
		}
	}
	return false;
}


