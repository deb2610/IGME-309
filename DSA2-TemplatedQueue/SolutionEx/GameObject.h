#pragma once
#include <iostream>
#include <string>
//Homework 4 - Templated Stack
//Created by Declan E Behan for Austins DSA Class
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

