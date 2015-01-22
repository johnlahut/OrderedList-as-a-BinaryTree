/*
Author: Luke Musto
Modifications: John Lahut
Date: 12/2/2014
Last modified: 12/19/2014
Project: OrdList as a BST
Filename: OrdListADT.h
Purpose: Provides the specification for an ordered list implemented with a BST. 
		Client will interact with the list just like any other list based ADT. However, behind the scenes, the list is implelemented as a
		binary search tree. Most operations attempt to be O(H) where H is the height of the tree. 
Input: All input is done via client
Output: Supports a function pointer containing a output file stream. Client handles formatting of all print functions
Assumptions: All items are stored by a KeyType key. Currently the KeyType is set to an integer value. 
*/


#include <iostream>
#include <fstream>
#include "ItemType.h"
using namespace std;

typedef void(*FunctionType)(const ItemType&);

typedef void(*FunctionTypeFile)(const ItemType&, ofstream&);

// IMPORTANT: PLEASE NOTE:  THIS IS A CLASS TEMPLATE,  THEREFORE: 
//				(1) THE STRUCT ItemType DECLARATION MUST BE SUPPLIED BY CLIENT AND 
//						APPEAR ABOVE THE MAIN. 
//				(2) IT SHOULD CONTAIN A FIELD OF KeyType CALLED key.
//						This will be used to order the list.
//				(3) KeyType SHOULD APPEAR AS A typedef ABOVE THE ItemType DECLARATION in the client.
//				
// A forward declaration should be used and appears below 
struct node;

/*

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~                                            ~
~              Public Methods				 ~
~                                            ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OrdListClass();
	a new OrdListClas has been created with all values set to nullptr

~OrdListClass();
	current OrdListClass has been deallocated from memory

OrdListClass(const OrdListClass &orig)
	creates a deep copy of orig

bool  IsEmpty()const;
	returns true to the caller if the list is empty, false otherwise

bool  IsFull()const;
	returns true to the caller if the list is full, false otherwise

bool  EndOfList();
	returns true to the caller if at the end of the list. End of list is one element past the end of
	the list. This is represented by currPos == prevPos

void  FirstPosition();
	sets the current position of the list to the next greatest element in the list

void  NextPosition();
	sets the current position of the list to the next greatest element in the list

void  LastPosition();
	sets the current position of the list to the last (greatest) element in the list

bool Find(KeyType key);
	returns true to the caller if the key was found, false otherwise. currPos is either set to the
	found node or where the node would appear in the list

ItemType Retrieve()const;
	returns the current index of the list to the caller

bool Insert(ItemType newItem)
	newItem is inserted into the correct position in the list

void Delete();
	the element at currPos has been removed from the list

void Clear();
	all elements have been removed from the list. All memory from nodes have been returned to freestore

int ReturnLength() const;
	returns the length of the current list to the caller

void PrintScreen(FunctionType visit);
	the current list has been printed to the console, formatted by the client

void PrintFile(FunctionTypeFile visit, string fileName);
	the current list has been printed to a file specified and formatted by the client. The file is printed
	in such a way that if it were to be read back in, an identical tree would be created
	
void PrintReverse(inoutFunctionType visit);
	the current list has been printed to the console backwards, formatted by the client

void PrintAsExists(FunctionType visit);
	the current list has been printed to the console formatted like a tree

virtual void operator=(const OrdListClass& rightOp);
	current object is identical to rightOp


virtual bool operator==(const OrdListClass& rightOp) const
	returns true to the caller if current objects keys are identical to rightOp, false otherwise


virtual bool operator!=(const OrdListClass& rightOp) const;
	returns true to the caller if current objects keys are not identical to rightOp, false otherwise

OrdListClass operator+(const OrdListClass& rightOp) const;
	returns a new OrdListClass with the union of the current objects keys and rightOp's keys. The new
	list is a near balanced/complete tree. Since the function creates a new object, and balances it, if
	an empty list was added to an unbalanced list, the returning list will be different even though nothing
	was added to the list

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~                                            ~
~              Protected Methods			 ~
~                                            ~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

node* Allocate();
	returns a new node pointer to the caller with all values set to nullptr

int rLength(node *trav, int &numNodes) const;
	traverses the list and returns the number of elements to the caller

void rDelete(node *&trav);
	given a node pointer, delete the current node maintaining proper order
	when prevPos is a nullptr, currPos is pointing to the root

void rPreOrderTrav(node *rtRoot);
	does a pre-order traversal of rtRoot and inserts them into the current object

void CreateTree(ItemType items[], OrdListClass& list, int start, int end) const;
	creates a BST from an ordered list of data and returns it to the caller by ref

void rInOrderTrav(FunctionType visit, node* trav);
	Traverses the list in order visiting each node. client defines what a "visit" is

void rFileTrav(FunctionTypeFile visit, ofstream& outdat);
	Traverses the list in order visiting each node. client defines what a "visit" is

void rBackwardInOrderTrav(FunctionType visit, node* trav);
	Traverses the list backwards visiting each node. client defines what a "visit" is

bool rFind(KeyType key);
	returns true to the caller if key is found in the current object, false otherwise. wrapped function
*/

class OrdListClass
{

public:

	/*****************************************************************************************************/

	//Pre: none	
	//Post: a new OrdListClas has been created with all values set to nullptr
	OrdListClass();  

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post:	 current OrdListClass has been deallocated from memory
	~OrdListClass();	

	/*****************************************************************************************************/

	//Pre: orig is a valid OrdListClass
	//Post: creates a deep copy of orig
	OrdListClass(/*in*/const OrdListClass &orig); //object to copy		

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns true to the caller if the list is empty, false otherwise
	bool  IsEmpty()const;	

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns true to the caller if the list is full, false otherwise
	bool  IsFull()const;  

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns true to the caller if at the end of the list. End of list is one element past the end of
	//		the list. This is represented by currPos == prevPos
	bool  EndOfList();					

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: sets the current position of the list to the first position
	void  FirstPosition();	

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: sets the current position of the list to the next greatest element in the list
	void  NextPosition();	

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: sets the current position of the list to the last (greatest) element in the list
	void  LastPosition();				

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, key is a valid KeyType
	//Post: returns true to the caller if the key was found, false otherwise. currPos is either set to the
	//		found node or where the node would appear in the list
	bool Find(/*in*/KeyType key); //key type to find

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns the current index of the list to the caller
	//Exceptions thrown: throws a RetrieveOnEmptyException if the caller attempts to Retrieve an item on an
	//					 empty list
	ItemType Retrieve()const;

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated , Find has been called to set currPos
	//Post: newItem is inserted into the correct position in the list
	//Exceptions thrown: throws a DuplicateKeyException if the caller attempts to insert a item that 
	//					 is already in the list
	bool Insert(/*in*/ItemType newItem); //item to insert into the list

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, Find has been called to set currPos to the element that needs
	//		to be deleted
	//Post: the element at currPos has been removed from the list
	void Delete();	

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: all elements have been removed from the list. All memory from nodes have been returned to freestore
	void Clear();   			 

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns the length of the current list to the caller
	int ReturnLength() const; 	   

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valud FunctonType. Client needs to match datatype
	//Post: the current list has been printed to the console, formatted by the client
	void PrintScreen(/*inout*/FunctionType visit); //function pointer. passes control back to client

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valid FunctionTypeFile. Client needs to match datatype
	//Post: the current list has been printed to a file specified and formatted by the client. The file is printed
	//		in such a way that if it were to be read back in, an identical tree would be created
	void PrintFile( /*inout*/FunctionTypeFile visit,	//function pointer that passes control back to client. contains an ofstream 
					/*inout*/string fileName);			//filename to write the data to

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valid FunctonType. Client needs to match datatype
	//Post: the current list has been printed to the console backwards, formatted by the client
	void PrintReverse(/*inout*/FunctionType visit); //function pointer. passes control back to client

	/*****************************************************************************************************/
	
	//Pre: OrdListClass has been instantiated, visit is a valid FunctonType. Client needs to match datatype
	//Post: the current list has been printed to the console formatted like a tree
	void PrintAsExists(/*inout*/FunctionType visit); //function pointer. passes control back to client

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
	//Post: current object is identical to rightOp
	virtual void operator=(/*in*/const OrdListClass& rightOp); //object to be copied

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
	//Post: returns true to the caller if current objects keys are identical to rightOp, false otherwise
	virtual bool operator==(/*in*/const OrdListClass& rightOp) const; //object to compare to

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
	//Post: returns true to the caller if current objects keys are not identical to rightOp, false otherwise
	virtual bool operator!=(/*in*/const OrdListClass& rightOp) const; //object to compare to

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiatedm rightOp is a valid OrdListClass
	//Post: returns a new OrdListClass with the union of the current objects keys and rightOp's keys. The new
	//		list is a near balanced/complete tree. Since the function creates a new object, and balances it, if 
	//		an empty list was added to an unbalanced list, the returning list will be different even though nothing
	//		was added to the list
	OrdListClass operator+(/*in*/const OrdListClass& rightOp) const; //object to union

	/*****************************************************************************************************/

protected:

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated
	//Post: returns a new node pointer to the caller with all values set to nullptr
	//Exceptions thrown: throws an OutOfMemoryException when there is no more space left on the heap
	node* Allocate();

	/*****************************************************************************************************/

	//wrapped function
	//Pre: OrdListClass has been instantiated, trav is the root
	//Post: traverses the list and returns the number of elements to the caller
	int rLength(/*in*/node *trav,				//starting node
				/*inout*/int &numNodes) const;	//number of nodes in the tree

	/*****************************************************************************************************/
	
	//Pre: Find has been called on the node that needs to be deleted. OrdListClass has been instantiated
	//Post: given a node pointer, delete the current node maintaining proper order
	//when prevPos is a nullptr, currPos is pointing to the root
	//wrapped function (sort of) will only call itself at most one additional time
	void rDelete(/*inout*/node *&trav);  //node to delete from the current object

	/*****************************************************************************************************/

	//Pre: rtRoot is a valid root of a tree, OrdListClass has been instantiated
	//Post: does a pre-order traversal of rtRoot and inserts them into the current object
	void rPreOrderTrav(/*in*/node *rtRoot); //root of tree to copy

	/*****************************************************************************************************/

	//Pre: items is an ordered array with ItemTypes to be added to list
	//		list is a valid OrdListClass
	//		start is the starting index of the search (init 0) 
	//		end is the end of the search (init items.size)
	//Post: creates a BST from an ordered list of data and returns it to the caller by ref
	void CreateTree(	/*in*/ItemType items[],			//sorted list of elements 
						/*inout*/OrdListClass& list,	//list to be created
						/*in*/int start,				//starting index
						/*in*/int end) const;			//ending index

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valid FunctonType, trav is typically root (init)
	//Post: Traverses the list in order visiting each node. client defines what a "visit" is
	void rInOrderTrav(	/*inout*/FunctionType visit,	//function pointer (passes control to client)
						/*in*/node* trav);				//current node

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valid FunctonTypeFile, trav is typically root (init)
	//Post: Traverses the list in order visiting each node. client defines what a "visit" is
	void rFileTrav(	/*inout*/FunctionTypeFile visit, //function pointer (passes control to client) 
					/*in*/node* trav,				 //current node
					/*inout*/ofstream& outdat);		 //out file stream

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated, visit is a valid FunctonType, trav is typically root (init)
	//Post: Traverses the list backwards visiting each node. client defines what a "visit" is
	void rBackwardInOrderTrav(	/*inout*/FunctionType visit,	//function pointer (passes control to client)
								/*in*/node* trav);				//current node

	/*****************************************************************************************************/

	//Pre: OrdListClass has been instantiated. key is a valid KeyType
	//Post: returns true to the caller if key is found in the current object, false otherwise. wrapped function
	bool rFind(/*in*/KeyType key); //key to find

	/*****************************************************************************************************/


private:


	node* root;			//root node
	node* currPos;		//current position in the list
	node* prevPos;		//not nes. the preceeding node, but always the parent of currPos. nullptr when currPos == root

};
