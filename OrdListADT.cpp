/*
Author: Luke Musto
Modifications: John Lahut
Date: 12/2/2014
Last modified: 12/19/2014
Project: OrdList as a BST
Filename: OrdListADT.h
Purpose: Provides the implementation for an ordered list implemented with a BST.
Client will interact with the list just like any other list based ADT. However, behind the scenes, the list is implelemented as a
binary search tree. Most operations attempt to be O(H) where H is the height of the tree.
Input: All input is done via client
Output: Supports a function pointer containing a output file stream. Client handles formatting of all print functions
Assumptions: All items are stored by a KeyType key. Currently the KeyType is set to an integer value.
*/


#include "OrdListADT.h"
#include "Exceptions.h"


#include <iostream>

using namespace std;

struct node
{
	ItemType data;
	node *left;
	node *right;
};


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

/*****************************************************************************************************/

//Pre: none	
//Post: a new OrdListClas has been created with all values set to nullptr
OrdListClass::OrdListClass()
{
	root = nullptr;
	prevPos = nullptr;
	currPos = nullptr;

}//end default constructor


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post:	 current OrdListClass has been deallocated from memory
OrdListClass::~OrdListClass()
{
	Clear();

}//end destructor


/*****************************************************************************************************/

//Pre: orig is a valid OrdListClass
//Post: creates a deep copy of orig
OrdListClass::OrdListClass(/*in*/const OrdListClass &orig) //object to copy
{
	root = nullptr;
	prevPos = nullptr;
	currPos = nullptr; 

	operator=(orig);

}//end copy constructor


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns true to the caller if the list is empty, false otherwise
bool OrdListClass::IsEmpty() const
{
	return(root == nullptr);

}//end IsEmpty


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns true to the caller if the list is full, false otherwise
bool OrdListClass::IsFull() const
{
	return false;

}//end IsFull


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns true to the caller if at the end of the list. End of list is one element past the end of
//		the list. This is represented by currPos == prevPos
bool OrdListClass::EndOfList()
{
	return (currPos==prevPos);

}//end EndOfList


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: sets the current position of the list to the first position
void OrdListClass::FirstPosition()
{

	//First position is the left most node

	currPos = root;
	if (currPos != nullptr)
	{
		while (currPos->left != nullptr)
		{
			prevPos = currPos;
			currPos = currPos->left;

		}//end while

	}//end if

}//end FirstPosition


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: sets the current position of the list to the next greatest element in the list
void OrdListClass::NextPosition()
{
	//uses Find to correctly set currPos and prevPos


	if (!IsEmpty() && !EndOfList())
	{

		//To compinsate for last postion... if the current position is the last position in the list, 
		//only change prevPos so that it equals currPos (end of list)

		node *temp = root;
		while (temp->right != nullptr)
		{
			temp = temp->right;

		}//end while

		//Last position
		if (temp == currPos)
		{
			prevPos = currPos;

		}//end if


		//If the right sub tree is not null, find the next in order precursor
		else if (currPos->right != nullptr)
		{
			prevPos = currPos;
			currPos = currPos->right;
			while (currPos->left != nullptr)
			{
				prevPos = currPos;
				currPos = currPos->left;
				
			}//end while

		}//end else if


		//prevPos always is pointing to the parent node. null if the current position is the root.
		
		else if (prevPos != nullptr)
		{
			if (prevPos->left == currPos)
			{
				Find(prevPos->data.key);

			}//end if

			else //currPos is in prevPos's right subtree. need to go up one level
			{
				while (currPos == prevPos->right)
				{
					Find(prevPos->data.key);

				}//end while

				currPos = prevPos;
				Find(currPos->data.key);

			}//end else

		}//end else if

	}//end if

}//end NextPosition


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: sets the current position of the list to the last (greatest) element in the list
void OrdListClass::LastPosition()
{
	//Last position is the right most node

	currPos = root;

	while (currPos->right != nullptr)
	{
		currPos = currPos->right;

	}//end while

	prevPos = currPos;

}//end LastPosition


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, key is a valid KeyType
//Post: returns true to the caller if the key was found, false otherwise. currPos is either set to the
//		found node or where the node would appear in the list
bool OrdListClass::Find(/*in*/KeyType key) //key type to find
{
	currPos = root;
	return rFind(key);

}//end Find


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns the current index of the list to the caller
//Exceptions thrown: throws a RetrieveOnEmptyException if the caller attempts to Retrieve an item on an
//					 empty list
ItemType OrdListClass::Retrieve() const
{
	if (root != nullptr)
		return currPos->data;
	else
		throw RetrieveOnEmptyException();


}//end Retrieve


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated , Find has been called to set currPos
//Post: newItem is inserted into the correct position in the list
//Exceptions thrown: throws a DuplicateKeyException if the caller attempts to insert a item that 
//					 is already in the list
bool OrdListClass::Insert(/*in*/ItemType newItem) //item to insert into the list
{


	//First element in the list
	if (root == nullptr)
	{
		root = Allocate();
		root->data = newItem;
		return true;

	}//end if

	//currPos should point to null here 
	//Find has already been called and currPos points to where the new element should go. If the element
	//was found in the list, currPos will not point to null
	else
	{
		if (currPos != nullptr)
		{
			throw new DuplicateKeyException();

		}//end if

		currPos = Allocate();
		currPos->data = newItem;

		//prevPos always points to parent node. Linking the nodes together
		if (currPos->data.key < prevPos->data.key)
		{
			prevPos->left = currPos;

		}//end if
		else
		{
			prevPos->right = currPos;

		}//end else

		return true;

	}//end else

	return false;

}//end Insert


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, Find has been called to set currPos to the element that needs
//		to be deleted
//Post: the element at currPos has been removed from the list
void OrdListClass::Delete()
{
	rDelete(currPos);

}//end Delete


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: all elements have been removed from the list. All memory from nodes have been returned to freestore
void OrdListClass::Clear()
{
	//while list is not empty, delete the smallest node
	while (root != nullptr)
	{
		FirstPosition();
		Delete();

	}//end while

}//end Clear


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns the length of the current list to the caller
int OrdListClass::ReturnLength() const
{
	//TODO: header record for root?? O(n) runtime for getlength...

	int count = 0;
	rLength(root, count);
	return count;

}//end ReturnLength


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonType. Client needs to match datatype
//Post: the current list has been printed to the console, formatted by the client
void OrdListClass::PrintScreen(/*inout*/FunctionType visit) //function pointer. passes control back to client
{
	rInOrderTrav(visit, root);

}//end PrintScreen


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctionTypeFile. Client needs to match datatype
//Post: the current list has been printed to a file specified and formatted by the client. The file is printed
//		in such a way that if it were to be read back in, an identical tree would be created
void OrdListClass::PrintFile(/*inout*/FunctionTypeFile visit,	//function pointer that passes control back to client. contains an ofstream 
							 /*inout*/string fileName)			//filename to write the data to
{
	ofstream outdat(fileName);
	rFileTrav(visit, root, outdat);

}//end PrintFile


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonType. Client needs to match datatype
//Post: the current list has been printed to the console backwards, formatted by the client
void OrdListClass::PrintReverse(/*inout*/FunctionType visit) //function pointer. passes control back to client
{
	rBackwardInOrderTrav(visit, root);

}//end PrintReverse


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonType. Client needs to match datatype
//Post: the current list has been printed to the console formatted like a tree
void OrdListClass::PrintAsExists(/*inout*/FunctionType visit) //function pointer. passes control back to client
{

}//end PrintAsExists


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
//Post: current object is identical to rightOp
void OrdListClass::operator=(/*in*/const OrdListClass& rightOp) //object to be copied
{
	Clear();
	node *rtRoot = rightOp.root;
	rPreOrderTrav(rtRoot);

	currPos = rightOp.currPos;
	prevPos = rightOp.prevPos;

}//end operator=


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
//Post: returns true to the caller if current objects keys are identical to rightOp, false otherwise
bool OrdListClass::operator==(/*in*/const OrdListClass& rightOp) const //object to compare to
{
	//Need to set their roots back to null right before the return statement because the left and right lists point
	//to the same root as this and rightOp and leave scope, invoking the destructor, destroying the root of
	//this and rightOp. (do you know how long it took me to figure this out?!)

	OrdListClass leftList; OrdListClass rightList;

	leftList.root = root; rightList.root = rightOp.root;


	//If the lists do not have the same length, stop here
	if (leftList.ReturnLength() != rightList.ReturnLength())
	{
		leftList.root = nullptr; rightList.root = nullptr;
		return false;

	}//end if

	else
	{

		//Traverse each list starting from least element moving to greatest checking each element in the list
		leftList.FirstPosition(); rightList.FirstPosition();

		while (!leftList.EndOfList())
		{
			if (leftList.currPos->data.key != rightList.currPos->data.key)
			{
				leftList.root = nullptr; rightList.root = nullptr;
				return false;

			}//end if

			else
			{
				leftList.NextPosition();
				rightList.NextPosition();
			}//end else

		}//end while

	}//end else


	leftList.root = nullptr; rightList.root = nullptr;

	return true;

}//end operator==


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, rightOp is a valid OrdListClass
//Post: returns true to the caller if current objects keys are not identical to rightOp, false otherwise
bool OrdListClass::operator!=(/*in*/const OrdListClass& rightOp) const //object to compare to
{
	return !(operator==(rightOp));

}//end operator!=


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiatedm rightOp is a valid OrdListClass
//Post: returns a new OrdListClass with the union of the current objects keys and rightOp's keys. The new
//		list is a near balanced/complete tree. Since the function creates a new object, and balances it, if 
//		an empty list was added to an unbalanced list, the returning list will be different even though nothing
//		was added to the list
OrdListClass OrdListClass::operator+(/*in*/const OrdListClass& rightOp) const //object to union
{
	//For operator+ I copy both lists into temporary OrdListClasses. Then, go through each element in the list adding them to a
	//dynamic array of ItemTypes (in order). Then, passing the array and number of elements into a helper function, an OrdListClass 
	//is created using the sorted array using a modifed binary search


	OrdListClass leftList; OrdListClass rightList; OrdListClass result;

	ItemType left; ItemType right; //current Items
	int index = 0;					//number of items in new tree



	leftList.root = root; rightList.root = rightOp.root;
	int leftLen = leftList.ReturnLength(); int rightLen = rightList.ReturnLength();
	ItemType* items = new ItemType[leftLen + rightLen]; //dynamic array (unknown tree sizes)

	leftList.FirstPosition(); rightList.FirstPosition();


	//while one of the lists is not at the end
	while (!leftList.EndOfList() && !rightList.EndOfList())
	{

		//add the lesser key first

		left = leftList.Retrieve(); right = rightList.Retrieve();
		if (left.key < right.key) 
		{
			items[index] = left;
			leftList.NextPosition();

		}//end if

		else if (left.key > right.key)
		{
			items[index] = right;
			rightList.NextPosition();

		}//end else if

		else
		{
			items[index] = left;
			rightList.NextPosition();
			leftList.NextPosition();

		}//end else

		++index;

	}//end while

	//Add the left over elements from the list that did not reach the end

	if (leftList.EndOfList())
	{
		while (!rightList.EndOfList())
		{
			right = rightList.Retrieve();
			items[index] = right;
			rightList.NextPosition();
			++index;

		}//end while

	}//end if

	else if (rightList.EndOfList())
	{
		while (!leftList.EndOfList())
		{
			left = leftList.Retrieve();
			items[index] = left;
			leftList.NextPosition();
			++index;

		}//end while

	}//end else if


	//Create a balanced tree
	CreateTree(items, result, 0, index - 1);

	//clear root pointers
	leftList.root = nullptr; rightList.root = nullptr;

	return result;

}//end operator+


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated
//Post: returns a new node pointer to the caller with all values set to nullptr
//Exceptions thrown: throws an OutOfMemoryException when there is no more space left on the heap
node* OrdListClass::Allocate()
{
	try
	{
		node* temp = new node;
		temp->left = nullptr;
		temp->right = nullptr;
		return temp;

	}//end try

	catch (bad_alloc*)
	{
		throw new OutOfMemoryException;

	}//end catch

}//end Allocate


/*****************************************************************************************************/

//wrapped function
//Pre: OrdListClass has been instantiated, trav is the root
//Post: traverses the list and returns the number of elements to the caller
int OrdListClass::rLength(/*in*/node *trav,				//starting node
						 /*inout*/int &numNodes) const	//number of nodes in the tree
{
	if (trav != nullptr)				
	{
		numNodes++;						//increment counter
		rLength(trav->left, numNodes);	//go left
		rLength(trav->right, numNodes);	//go right

	}//end if

	return numNodes;

}//end rLength


/*****************************************************************************************************/

//Pre: Find has been called on the node that needs to be deleted. OrdListClass has been instantiated
//Post: given a node pointer, delete the current node maintaining proper order
//when prevPos is a nullptr, currPos is pointing to the root
//wrapped function (sort of) will only call itself at most one additional time
void OrdListClass::rDelete(/*inout*/node *&trav)  //node to delete from the current object
{
	if (trav->left == nullptr && trav->right == nullptr) //no children
	{
		if (trav != root)			//no children, and at the root therefore the root is the only node left in the tree, need to delete that node so go to else..
		{
			if (prevPos->left == trav)
			{
				prevPos->left = nullptr;

			}//end if

			else
			{
				prevPos->right = nullptr;

			}//end else

		}//end if

		else
		{
			root = nullptr;
			prevPos = nullptr;

		}//end else

		delete trav;
		trav = root;

	}//end if

	else if (trav->left != nullptr && trav->right == nullptr) //Node we are trying to delete has a left child
	{
		node *temp = trav;

		if (trav != root)
		{
			if (prevPos->left == trav) //finding its parent to link together
			{
				prevPos->left = trav->left;

			}//end if

			else
			{
				prevPos->right = trav->left;

			}//end else

		}//end if

		else
		{
			root = trav->left;
			prevPos = nullptr;

		}//end else

		trav = root;
		delete temp;

	}//end else if

	else if (trav->left == nullptr && trav->right != nullptr) //node we are trying to delete has a right child
	{
		node *temp = trav;

		if (trav != root)
		{
			if (prevPos->left == trav)
			{
				prevPos->left = trav->right;

			}//end if

			else
			{
				prevPos->right = trav->right;

			}//end else

		}//end if

		else
		{
			root = trav->right;
			prevPos = nullptr;

		}//end else

		trav = root;
		delete temp;

	}//end else if

	else //node has two children. need to find in order precursor, copy its value, then process delete on the node that was copied
	{
		node *temp = trav;
		trav = trav->right;

		while (trav->left != nullptr)
		{
			trav = trav->left;

		}//end while

		Find(trav->data.key); //to set prev pos
		temp->data = trav->data;
		rDelete(trav);

	}//end else

}//end rDelete


/*****************************************************************************************************/

//Pre: rtRoot is a valid root of a tree, OrdListClass has been instantiated
//Post: does a pre-order traversal of rtRoot and inserts them into the current object
void OrdListClass::rPreOrderTrav(/*in*/node *rtRoot) //root of tree to copy
{
	if (rtRoot != nullptr)
	{
		Find(rtRoot->data.key);
		Insert(rtRoot->data);
		rPreOrderTrav(rtRoot->left);
		rPreOrderTrav(rtRoot->right);

	}//end if

}//end rPreOrderTrav


/*****************************************************************************************************/

//Pre: items is an ordered array with ItemTypes to be added to list
//		list is a valid OrdListClass
//		start is the starting index of the search (init 0) 
//		end is the end of the search (init items.size)
//Post: creates a BST from an ordered list of data and returns it to the caller by ref
void OrdListClass::CreateTree(	/*in*/ItemType items[],			//sorted list of elements 
								/*inout*/OrdListClass& list,	//list to be created
								/*in*/int start,				//starting index
								/*in*/int end) const			//ending index
{

	//slightly modified binary search. Instead of checking if the mp is our target, we add the array's mp value
	//to the tree. this creates the most balanced complete tree possible given a sorted array (i think)
	if (start <= end)
	{
		int mp = (start + end) / 2;

		list.Find(items[mp].key);
		list.Insert(items[mp]);
		CreateTree(items, list, start, mp - 1);
		CreateTree(items, list, mp + 1, end);

	}//end if

}//end CreateTree


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonType, trav is typically root (init)
//Post: Traverses the list in order visiting each node. client defines what a "visit" is
void OrdListClass::rInOrderTrav(/*inout*/FunctionType visit,	//function pointer (passes control to client)
								/*in*/node* trav)				//current node
{
	if (trav != nullptr)
	{
		rInOrderTrav(visit, trav->left);
		visit(trav->data);
		rInOrderTrav(visit, trav->right);

	}//end if

}//end InOrderTrav


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonTypeFile, trav is typically root (init)
//Post: Traverses the list in order visiting each node. client defines what a "visit" is
void OrdListClass::rFileTrav(	/*inout*/FunctionTypeFile visit, //function pointer (passes control to client) 
								/*in*/node* trav,				 //current node
								/*inout*/ofstream& outdat)		 //out file stream
{
	//Prints each node in a pre-order fashion so that when the nodes are read back in to a class,
	//An identical tree will have been created


	if (trav != nullptr)
	{
		visit(trav->data, outdat);
		rFileTrav(visit, trav->left, outdat);
		rFileTrav(visit, trav->right, outdat);
		
	}//end if

}//end rFileTrav


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated, visit is a valid FunctonType, trav is typically root (init)
//Post: Traverses the list backwards visiting each node. client defines what a "visit" is
void OrdListClass::rBackwardInOrderTrav(/*inout*/FunctionType visit,	//function pointer (passes control to client)
										/*in*/node* trav)				//current node
{
	//Visit in  a RNL fashion


	if (trav != nullptr)
	{
		rBackwardInOrderTrav(visit, trav->right);
		visit(trav->data);
		rBackwardInOrderTrav(visit, trav->left);

	}//end if

}//end rBackwardInOrderTrav


/*****************************************************************************************************/

//Pre: OrdListClass has been instantiated. key is a valid KeyType
//Post: returns true to the caller if key is found in the current object, false otherwise. wrapped function
bool OrdListClass::rFind(/*in*/KeyType key) //key to find
{

	if (currPos != nullptr)
	{

		if (currPos->data.key == key)
		{
			if (currPos == root)
			{
				prevPos = nullptr;

			}//end if

			return true;

		}//end if 

		else if (currPos->data.key < key) //go right
		{
			prevPos = currPos;
			currPos = currPos->right;
			return rFind(key);

		}//end else if

		else
		{
			prevPos = currPos;
			currPos = currPos->left;
			return rFind(key);

		}//end else

	}//end if

	else
	{
		return false;

	}//end else

}//end rFind



















