/*************************************
Program: LinkedList.h
Course: OOPDS
Year: 2015/16 Trimester 2
Name: NICHOLAS TAN YU ZHE
ID: 1142701655
Lecture: TC102
Lab: TT04
Email: nicholas.290696@gmail.com
Phone: 016-7768182
*************************************/

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
   Node<ItemType>* headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items

   int counter;
   
   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<ItemType>* getNodeAt(int position) const;

public:
   LinkedList();
   LinkedList(const LinkedList<ItemType>& aList);
   virtual ~LinkedList();

   int getCounter() const;
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool sortInsert(const ItemType& newEntry);
   bool remove(int position);
   void clear();
   
   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);

   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   void setEntry(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcep);
    ItemType operator[](int position);
}; // end LinkedList

#include "LinkedList.cpp"
#endif 
