/* Program		: Patient.cpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Patient class method definitions
*/
#include "Patient.hpp"

/* Method name	: Patient class 2 argument constructor
*  Accepts		: string containing patient name, int containing patients priority
*  Returns		: N/A
*/
Patient::Patient(std::string n, int p)
{
	this->name = new std::string(n);
	this->priority = new int(p);
}

/* Method name	: Patient copy constructor
*  Accepts		: Patient reference to be copied
*  Returns		: N/A
*  Note			: Does not pass by const & because we need to access the nodes getters
*/
Patient::Patient(Patient & p)
{
	this->name = new std::string(p.getName());
	this->priority = new int(p.getPriority());
	ListNode<Injury>* tmp = p.Ilist->getNode(0);
	while (tmp != nullptr) {
		this->Ilist->addTail(new Injury(tmp->getData()->getDiagnosis(), tmp->getData()->getPriority()));
		tmp = tmp->next;
	}
}

/* Method name	: Patient class Destructor
*  Accepts		: N/A
*  Returns		: N/A
*  Description	: DESTROYS the patient  .... Fatality
*/
Patient::~Patient()
{
	delete this->name;
	delete this->priority;
	delete this->Ilist;
}

// Getters and setters
int Patient::getPriority()
{
	return *this->priority;
}
void Patient::setPriority(int p)
{
	delete this->priority;
	this->priority = new int(p);

}
std::string Patient::getName()
{
	return *this->name;
}
void Patient::setName(std::string* n)
{
	delete this->name;
	name = n;
}

/* Method name	: addToList
*  Accepts		: string - Injury name, int type, int contagious, int time criticallity, int severity
*  Returns		: void
*  Description	: Adds an injury to the patients injury list
*/
void Patient::addToList(std::string injuryName, int type, int cont, int time, int sev)
{
	int priority = ((type + sev) / time) + cont;
	Ilist->addTail(new Injury(injuryName, priority));
	if (priority >= 3 || this->getPriority() == 0) {
		int newPriority = this->getPriority() + priority;
		this->setPriority(newPriority);
	}
}

/* Method name	: traverseData
*  Accepts		: nothing
*  Returns		: void
*  Description	: Traverses the patient data
*/
void Patient::traverseData()
{
	std::cout << this->getName() << " - ";
	printInjuries();
	std::cout << std::endl;
}

/* Method name	: printInjuries
*  Accepts		: nothing
*  Returns		: void
*  Description	: Prints all the patients injuries
*/
void Patient::printInjuries()
{
	if (this->Ilist->getSize() == 0) {
		return;
	}
	ListNode<Injury>* tmp = this->Ilist->getNode(0);
	while (tmp != nullptr) {
		std::cout << "| " << tmp->getData()->getDiagnosis() << " ";
		tmp = tmp->next;
	}
}

