/*-------------------------------------------------------------------------------------------------- 
Declan E. Behan
DSA 2 Section 2

Homework 1 - Templated Queue
for Alberto's DSA 2 Class
--------------------------------------------------------------------------------------------------*/ 
#include "Main.h"

#define _CRTDBG_MAP_ALLOC
#include "pch.h"
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include "TemplatedQueue.h"
#include "GameObject.h"

using namespace std;
//wrapper function
void doQueuePlease() {

	//create Queue
	TemplatedQueue<int> numQueue = TemplatedQueue<int>();

	cout << "IsEmpty? : " << numQueue.IsEmpty() << endl << endl;

	//pusch to Queue
	numQueue.Push(10);
	numQueue.Push(23);
	numQueue.Push(5);

	//print
	numQueue.Print();

	//show data
	cout << endl;
	cout << "Queue Size:" << numQueue.getSize() << endl;
	cout << "Queue Max: " << numQueue.getSizeMax() << endl;
	cout << "Queue Top: " << numQueue.getTopIndex() << endl;
	cout << endl;
	cout << "Popped off: " << numQueue.Pop() << endl;
	cout << endl;

	//show pops work
	numQueue.Print();

	cout << endl;
	cout << "IsEmpty? : " << numQueue.IsEmpty() << endl << endl;

	numQueue.Push(11);
	numQueue.Push(2);

	numQueue.Print();

	cout << endl;
	cout << "Popped off: " << numQueue.Pop() << endl;
	cout << endl;

	numQueue.Print();


	cout << "----------------------------------" << endl << endl;
	//create class Queue
	TemplatedQueue<GameObject> gameQueue = TemplatedQueue<GameObject>();

	cout << "IsEmpty? : " << gameQueue.IsEmpty() << endl << endl;

	//create objects
	GameObject go0 = GameObject();
	GameObject go1 = GameObject("Shiv", 120001);
	GameObject go2 = GameObject("Gold", 200000);

	//push them to the Queue
	gameQueue.Push(go0);
	gameQueue.Push(go1);
	gameQueue.Push(go2);

	//tell us about em
	gameQueue.Print();

	//data please
	cout << endl;
	cout << "Queue Size:" << gameQueue.getSize() << endl;
	cout << "Queue Max: " << gameQueue.getSizeMax() << endl;
	cout << "Queue Top: " << gameQueue.getTopIndex() << endl;
	cout << endl;
	cout << "Popped off: " << gameQueue.Pop() << endl;
	cout << endl;

	//popping works
	gameQueue.Print();

	cout << endl;
	cout << "IsEmpty? : " << gameQueue.IsEmpty() << endl << endl;

	//cout << "---Extra Credit---" << endl;
	//cout << "Queue Data at index 1:" << numQueue[1] << endl;


}
//main method my dude
int main() {
	//std::cout << "Hello World\n";
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	doQueuePlease();
	//_CrtDumpMemoryLeaks();
	std::cout << "Press enter to finish"; 
	getchar(); 
	return 0; 
}