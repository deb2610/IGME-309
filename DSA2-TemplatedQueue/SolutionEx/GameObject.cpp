#include "pch.h"
#include "GameObject.h"
//Homework 4 - Templated Stack
//Created by Declan E Behan for Austins DSA Class
//constructor
GameObject::GameObject()
{
	name = "DEFAULT";
	id = 000000;
}
//better constuctor
GameObject::GameObject(string _name, int _id)
{
	name = _name;
	id = _id;
}

//delet
GameObject::~GameObject()
{
}
//im tired
ostream & operator<<(ostream& ostr, const GameObject& rhs)
{
	ostr << rhs.name << "[" << rhs.id << "]";
	return ostr;
}
