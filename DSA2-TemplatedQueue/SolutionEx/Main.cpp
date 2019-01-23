/*-------------------------------------------------------------------------------------------------- 
Declan E. Behan
DSA 2 Section 2

Homework 1 - Templated Stack
for Alberto's DSA 2 Class
--------------------------------------------------------------------------------------------------*/ 
#include "Main.h"

#define _CRTDBG_MAP_ALLOC
#include "pch.h"
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include "TemplatedStack.h"
#include "GameObject.h"

using namespace std;
//wrapper function
void doStackPlease() {

	//create stack
	TemplatedStack<int> numStack = TemplatedStack<int>();

	cout << "IsEmpty? : " << numStack.IsEmpty() << endl << endl;

	//pusch to stack
	numStack.Push(10);
	numStack.Push(23);
	numStack.Push(5);

	//print
	numStack.Print();

	//show data
	cout << endl;
	cout << "Stack Size:" << numStack.getSize() << endl;
	cout << "Stack Max: " << numStack.getSizeMax() << endl;
	cout << "Stack Top: " << numStack.getTopIndex() << endl;
	cout << endl;
	cout << "Popped off: " << numStack.Pop() << endl;
	cout << endl;

	//show pops work
	numStack.Print();

	cout << endl;
	cout << "IsEmpty? : " << numStack.IsEmpty() << endl << endl;

	cout << "----------------------------------" << endl << endl;
	//create class stack
	TemplatedStack<GameObject> gameStack = TemplatedStack<GameObject>();

	cout << "IsEmpty? : " << gameStack.IsEmpty() << endl << endl;

	//create objects
	GameObject go0 = GameObject();
	GameObject go1 = GameObject("Shiv", 120001);
	GameObject go2 = GameObject("Gold", 200000);

	//push them to the stack
	gameStack.Push(go0);
	gameStack.Push(go1);
	gameStack.Push(go2);

	//tell us about em
	gameStack.Print();

	//data please
	cout << endl;
	cout << "Stack Size:" << gameStack.getSize() << endl;
	cout << "Stack Max: " << gameStack.getSizeMax() << endl;
	cout << "Stack Top: " << gameStack.getTopIndex() << endl;
	cout << endl;
	cout << "Popped off: " << gameStack.Pop() << endl;
	cout << endl;

	//popping works
	gameStack.Print();

	cout << endl;
	cout << "IsEmpty? : " << gameStack.IsEmpty() << endl << endl;

	//cout << "---Extra Credit---" << endl;
	//cout << "Stack Data at index 1:" << numStack[1] << endl;


}
//main method my dude
int main() {
	std::cout << "Hello World\n";
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	doStackPlease();
	//_CrtDumpMemoryLeaks();
	std::cout << "Press enter to finish"; 
	getchar(); 
	return 0; 
}