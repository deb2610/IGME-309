#pragma once
#include <iostream>
#include <string>
/*--------------------------------------------------------------------------------------------------
Declan E. Behan
DSA 2 Section 2

Homework 1 - Templated Queue
for Alberto's DSA 2 Class
--------------------------------------------------------------------------------------------------*/
using namespace std;

class GameObject
{
public:
	//public variables
	GameObject();
	GameObject(string _name, int _id);
	~GameObject();
	string name;
	int id;
	friend ostream& operator<<(ostream& ostr, GameObject const& rhs);
};

