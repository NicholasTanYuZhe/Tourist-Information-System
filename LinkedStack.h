/*************************************
Program: LinkedStack.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef _LINKED_STACK
#define _LINKED_STACK

#include "StackInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

/** ADT stack - Linked implementation. */

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
	
private:
	Node<ItemType>* topPtr; // Pointer to first node in the chain;
                           // this node contains the stack's top

public:
// Constructors and destructor:
	LinkedStack();                                     // Default constructor
	LinkedStack(const LinkedStack<ItemType>& aStack);  // Copy constructor
	virtual ~LinkedStack();                            // Destructor
	
// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop();

   /** @throw PrecondViolatedExcep if the stack is empty */
	ItemType peek() const throw(PrecondViolatedExcep);
}; // end LinkedStack

#include "LinkedStack.cpp"

#endif
