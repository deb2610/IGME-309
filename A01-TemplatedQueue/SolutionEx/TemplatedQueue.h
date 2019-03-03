#pragma once
#include <iostream>
/*--------------------------------------------------------------------------------------------------
Declan E. Behan
DSA 2 Section 2

Homework 1 - Templated Queue
for Alberto's DSA 2 Class
--------------------------------------------------------------------------------------------------*/
using namespace std;
template <class T>
class TemplatedQueue
{
public:
	//Rule of Three (40%)
	TemplatedQueue();
	TemplatedQueue(const TemplatedQueue& other);
	TemplatedQueue& operator=(const TemplatedQueue& other);
	TemplatedQueue& operator[](int _index);
	~TemplatedQueue();

	//Getters
	T Pop();			//Pop Method (10%)
	int getSize();		//Gets the size of the Queue (10%)
	int getTopIndex();	//Gets the index of the top of the Queue
	int getSizeMax();	//Gets the memory size of the Queue
	
	//setters
	void Push(T _inData);		//Push Method (25%)
	void setSize(int _num);		//Setter to set sizeOfQueue
	void setTopIndex(int _num);	//Setter to set topOfQueue
	void setSizeMax(int _num);	//Setter to set maxSize

	//Other properties
	void Print();		//Print Method (10%)
	bool IsEmpty();		//IsEmpty Method (%5)
	void Sort();

private:
	//stored values
	T* data;			//Queue data
	int topOfQueue;		//index of the topmost data
	int sizeOfQueue;	//current size of Queue
	int maxSize;		//maximum size of Queue
};

template<class T>
//Rule of Three - Constructor
inline TemplatedQueue<T>::TemplatedQueue()
{
	topOfQueue = 0;
	sizeOfQueue = 0;
	maxSize = 8;
	data = new T[maxSize];
}

//Rule of Three - Copy Constructor
template<class T>
inline TemplatedQueue<T>::TemplatedQueue(const TemplatedQueue & other)
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
inline TemplatedQueue<T> & TemplatedQueue<T>::operator=(const TemplatedQueue & other)
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

//Extra Credit (DSA 1)- reassign [] Operator
template<class T>
inline TemplatedQueue<T> & TemplatedQueue<T>::operator[](int _index)
{
	return data[_index];
}

//Push Method - Method that adds data to the Queue
template<class T>
inline void TemplatedQueue<T>::Push(T _inData)
{	
	//if the size is 0 set the first data
	if (getSize() == 0)
	{
		data[0] = _inData;
		sizeOfQueue++;
	}
	//otherwise to the normal pushing
	else
	{
		//if there is room in the Queue
		sizeOfQueue++;
		//this increases the data when we need to
		if (maxSize <= sizeOfQueue)
		{
			setSizeMax(getSize() + 8);
		}
		//this handles the data storing
		else if (maxSize >= sizeOfQueue)
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

//Pop Method - Method returns the topmost item on the Queue then removes it
template<class T>
inline T TemplatedQueue<T>::Pop()
{
	//twist it! bop it! turn it! pop it!
	//T popped = data[getTopIndex()];
	T popped = data[0];
	for (size_t i = 0; i < sizeOfQueue; i++)
	{
		if (i+1 > sizeOfQueue)
		{
			break;
		}
		else {
			data[i] = data[i + 1];
		}
	}
	sizeOfQueue--;
	getTopIndex();
	return popped;//actually returns ;)
}

//Print Function - outputs the nice data for us
template<class T>
inline void TemplatedQueue<T>::Print()
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

//Sort Function - shall we sort the data?
template<class T>
inline void TemplatedQueue<T>::Sort()
{
	////loop through and then cout
	//for (size_t i = 0; i < getSize(); i++)
	//{
	//	if (getSize() == 0)
	//	{
	//		cout << "Data is size 0!" << endl;
	//		break;
	//	}
	//	else
	//	{
	//		cout << "CURRENT i = " << i << endl;
	//		//is the top thing the smaller than the bottom?
	//		if (data[getTopIndex()] <= data[i])
	//		{
	//			//cool than shift everthing down and put it at data[0]
	//			for (size_t j = getTopIndex(); j < getSize(); j--)
	//			{
	//				//cout << "TESTING data[" << j+1 << "] : " << data[j+1] << endl;
	//				data[j + 1] = data[j];
	//				cout << "TESTING data[" << j+1 << "] : " << data[j+1] << endl;

	//			}
	//			cout << "TOP INDEX'S DATA = " << data[getTopIndex()+1] << endl;
	//			data[i] = data[getTopIndex()+1];
	//			cout << "TESTING data[" << i << "] : " << data[i] << endl;

	//			cout << endl;
	//			Print();
	//			//
	//		}
	//	}
	//	
	//}
}

//Get Size - getter for sizeOfQueue
template<class T>
inline int TemplatedQueue<T>::getSize()
{
	return sizeOfQueue;
}

//Get Top Index - getter for topOfQueue
template<class T>
inline int TemplatedQueue<T>::getTopIndex()
{
	topOfQueue = getSize() - 1;
	return topOfQueue;
}

//Get Size Max - getter for maxSize
template<class T>
inline int TemplatedQueue<T>::getSizeMax()
{
	return maxSize;
}
//Set Size - setter for sizeOfQueue

template<class T>
inline void TemplatedQueue<T>::setSize(int _num)
{
	sizeOfQueue = _num;
}
//Set Top Index - setter for topOfQueue

template<class T>
inline void TemplatedQueue<T>::setTopIndex(int _num)
{
	topOfQueue = _num;
}

//Set Size Max - setter for maxSize
template<class T>
inline void TemplatedQueue<T>::setSizeMax(int _num)
{
	maxSize = _num;
}

//Is Empty - returns a bool for if the Queue is empty
template<class T>
inline bool TemplatedQueue<T>::IsEmpty()
{
	return getSize() == 0;
}

//Rule of Three - Destructor
template<class T>
inline TemplatedQueue<T>::~TemplatedQueue()
{
	//clean up out data
	delete[] data;
	data = nullptr;

	maxSize = 0;
	sizeOfQueue = 0;
	topOfQueue = 0;
}
