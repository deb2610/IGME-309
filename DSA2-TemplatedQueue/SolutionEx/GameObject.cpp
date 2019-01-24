#include "pch.h"
#include "GameObject.h"
/*--------------------------------------------------------------------------------------------------
Declan E. Behan
DSA 2 Section 2

Homework 1 - Templated Queue
for Alberto's DSA 2 Class
--------------------------------------------------------------------------------------------------*/
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
