/*
Author: John Lahut
Date: 12/19/2014
Project: OrdList as a BST
Filename: OrdListADT.h
Purpose: Provides the specification for exceptions thrown by OrdListClass
*/

//Thrown when client attempts to retrieve on an empty list
class RetrieveOnEmptyException{};

//thrown when client attempts to add a key into a tree that already exists
class DuplicateKeyException{};

//thrown when the freestore is out of memory
class OutOfMemoryException{};