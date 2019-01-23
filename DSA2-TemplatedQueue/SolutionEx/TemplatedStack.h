#pragma once
#include <iostream>
//Homework 4 - Templated Stack
//Created by Declan E Behan for Austins DSA Class
using namespace std;
template <class T>
class TemplatedStack
{
public:
	//Rule of Three (40%)
	TemplatedStack();
	TemplatedStack(const TemplatedStack& other);
	TemplatedStack& operator=(const TemplatedStack& other);
	TemplatedStack& operator[](int _index);
	~TemplatedStack();

	//Getters
	T Pop();			//Pop Method (10%)
	int getSize();		//Gets the size of the stack (10%)
	int getTopIndex();	//Gets the index of the top of the stack
	int getSizeMax();	//Gets the memory size of the stack
	
	//setters
	void Push(T _inData);		//Push Method (25%)
	void setSize(int _num);		//Setter to set sizeOfStack
	void setTopIndex(int _num);	//Setter to set topOfStack
	void setSizeMax(int _num);	//Setter to set maxSize

	//Other properties
	void Print();		//Print Method (10%)
	bool IsEmpty();		//IsEmpty Method (%5)

private:
	//stored values
	T* data;			//stack data
	int topOfStack;		//index of the topmost data
	int sizeOfStack;	//current size of stack
	int maxSize;		//maximum size of stack
};

template<class T>
//Rule of Three - Constructor
inline TemplatedStack<T>::TemplatedStack()
{
	topOfStack = 0;
	sizeOfStack = 0;
	maxSize = 8;
	data = new T[maxSize];
}

//Rule of Three - Copy Constructor
template<class T>
inline TemplatedStack<T>::TemplatedStack(const TemplatedStack & other)
{
	//copies allof the data over
	setSize(other.getSize);
	setSizeMax(other.getSizeMax);
	setTopIndex(other.getTopIndex);
	data = new T[maxSize];

	for (size_t i = 0; i < other.maxSize; i++)
	{
		data[i] = other.data[i];
	}
}

//Rule of Three - Copy Operator
template<class T>
inline TemplatedStack<T> & TemplatedStack<T>::operator=(const TemplatedStack & other)
{
	//re assignes the copy operator to deep copy the arrays
	if (this == &other)
	{
		return *this;
	}
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	setSize(other.getSize);
	setSizeMax(other.getSizeMax);
	setTopIndex(other.getTopIndex);
	data = new T[maxSize];

	copy(other.data, other.data + other.getSize, data);

	return *this;
}
//Extra Credit - reassign [] Operator
template<class T>
inline TemplatedStack<T> & TemplatedStack<T>::operator[](int _index)
{
	return data[_index];
}

//Push Method - Method that adds data to the stack
template<class T>
inline void TemplatedStack<T>::Push(T _inData)
{	
	//if the size is 0 set the first data
	if (getSize() == 0)
	{
		data[0] = _inData;
		sizeOfStack++;
	}
	//otherwise to the normal pushing
	else
	{
		//if there is room in the stack
		sizeOfStack++;
		//this increases the data when we need to
		if (maxSize <= sizeOfStack)
		{
			setSizeMax(getSize() + 8);
		}
		//this handles the data storing
		else if (maxSize >= sizeOfStack)
		{
			//gotta copy the current data to a new array but add the new info
			//Create newArray with new length
			T* newData = new T[getSizeMax() + 1];

			//Copy dataArray to newArray
			for (size_t i = 0; i < getSize(); i++)
			{
				newData[i] = data[i];
			}
			
			//add _inData at [length]

			newData[getTopIndex()] = _inData;

			//clean up leaky bois
			delete[] data;

			//repoint the data pointer
			data = newData;

		}
	}
	
}
//Pop Method - Method returns the topmost item on the stack then removes it
template<class T>
inline T TemplatedStack<T>::Pop()
{
	//twist it! bop it! turn it! pop it!
	T popped = data[getTopIndex()];
	sizeOfStack--;
	getTopIndex();
	return popped;//actually returns ;)
}

//Print Fucntion - outputs the nice data for us
template<class T>
inline void TemplatedStack<T>::Print()
{
	//loop through and then cout
	for (size_t i = 0; i < getSize(); i++)
	{
		if (getSize() == 0)
		{
			cout << "Data is size 0!" << endl;
			break;
		}
		cout << "Data at [" << i << "] : "<< data[i] << endl;
	}
}
//Get Size - getter for sizeOfStack
template<class T>
inline int TemplatedStack<T>::getSize()
{
	return sizeOfStack;
}
//Get Top Index - getter for topOfStack
template<class T>
inline int TemplatedStack<T>::getTopIndex()
{
	topOfStack = getSize() - 1;
	return topOfStack;
}
//Get Size Max - getter for maxSize
template<class T>
inline int TemplatedStack<T>::getSizeMax()
{
	return maxSize;
}
//Set Size - setter for sizeOfStack

template<class T>
inline void TemplatedStack<T>::setSize(int _num)
{
	sizeOfStack = _num;
}
//Set Top Index - setter for topOfStack

template<class T>
inline void TemplatedStack<T>::setTopIndex(int _num)
{
	topOfStack = _num;
}
//Set Size Max - setter for maxSize
template<class T>
inline void TemplatedStack<T>::setSizeMax(int _num)
{
	maxSize = _num;
}
//Is Empty - returns a bool for if the stack is empty
template<class T>
inline bool TemplatedStack<T>::IsEmpty()
{
	return getSize() == 0;
}

//Rule of Three - Destructor
template<class T>
inline TemplatedStack<T>::~TemplatedStack()
{
	//clean up out data
	delete[] data;
	data = nullptr;

	maxSize = 0;
	sizeOfStack = 0;
	topOfStack = 0;
}
