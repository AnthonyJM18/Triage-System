#pragma once
/* Program		: ListNode.hpp
*  Author		: Anthony Merante
*  Date			: November 3, 2019
*  Description	: Templated ListNode to be used with the templated LinkedList
*/

template <class T> class ListNode
{
private:
	// Private Member Variable
	T* data = nullptr;
	// 0-arg Constructor
	ListNode<T>() {};
public:
	// Public Member Variables
	ListNode<T>* next = nullptr;
	ListNode<T>* previous = nullptr;
	// 1-arg Constructor
	ListNode<T>(T* datain) { this->data = datain; }
	// Destructor
	~ListNode<T>() { if (this->data != nullptr) delete this->data; }
	// Class functions
	T* getData();
	T* getName();
	void setData(T* datain);
};



// Getters and Setters that use and return the templated type
template<class T>
T* ListNode<T>::getData()
{
	return this->data;
}

// This getter will use the method getName() that is defined in the templated types class definition
template<class T>
T* ListNode<T>::getName()
{
	return getData()->getName();
}

template<class T>
void ListNode<T>::setData(T* datain)
{
	this->data = datain;
}

