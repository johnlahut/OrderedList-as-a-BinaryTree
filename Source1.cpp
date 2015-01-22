/*
Author: John Lahut
Date: 12/19/2014
Project: OrdList as a BST
Filename: Source1.h
Purpose: Fully tests OrdListADT
*/

#include <iostream>
#include <fstream>

#include "OrdListADT.h"
#include "ItemType.h"
#include "Exceptions.h"

using namespace std;

void Display(const ItemType&);
void DisplayFile(const ItemType&, ofstream&);


void main()
{
	OrdListClass mylist, yourlist, theirlist, thatlist;
	ItemType item;

	item.key = 4;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 2;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 6;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 1;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 3;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 5;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 7;
	mylist.Find(item.key);
	mylist.Insert(item);

	item.key = 8;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 4;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 12;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 2;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 6;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 10;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 14;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 1;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 3;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 5;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 7;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 9;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 11;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 13;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 15;
	yourlist.Find(item.key);
	yourlist.Insert(item);

	item.key = 8;
	thatlist.Find(item.key);
	thatlist.Insert(item);

	item.key = 9;
	thatlist.Find(item.key);
	thatlist.Insert(item);

	item.key = 10;
	thatlist.Find(item.key);
	thatlist.Insert(item);

	item.key = 11;
	thatlist.Find(item.key);
	thatlist.Insert(item);

	cout << "My list" << endl; mylist.PrintScreen(Display);
	cout << "Your list" << endl; yourlist.PrintScreen(Display);
	cout << "Their list" << endl; theirlist.PrintScreen(Display);
	cout << "That list" << endl; thatlist.PrintScreen(Display);

	cout << "Testing operator =... theirList = myList" << endl;
	
	theirlist = mylist;

	cout << "My list" << endl; mylist.PrintScreen(Display);
	cout << "Their list" << endl; theirlist.PrintScreen(Display);

	cout << "Testing operator ==... theirList == myList" << endl;
	if (theirlist == mylist)
		cout << "PASSED." << endl;
	else
		cout << "FAILED." << endl;

	cout << "Testing operator !=... yourList == myList" << endl;
	if (yourlist!= mylist)
		cout << "PASSED." << endl;
	else
		cout << "FAILED." << endl;

	cout << "Testing operator +... myList == thatList" << endl;
	mylist = mylist + thatlist;
	mylist.PrintScreen(Display);

	cout << "Dumping all trees to their respecive output files" << endl;


	mylist.PrintFile(DisplayFile, "mylist.out");
	yourlist.PrintFile(DisplayFile, "yourlist.out");
	theirlist.PrintFile(DisplayFile, "theirlist.out");
	thatlist.PrintFile(DisplayFile, "thatlist.out");

}

void Display(const ItemType& recToDisplay)
{
	cout << recToDisplay.key << endl;
}

void DisplayFile(const ItemType& recToDisplay, ofstream& outdat)
{
	outdat << recToDisplay.key << endl;
}