/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	10-9-17
 *
 * File: Set.cc
 *
 * Assignment: Project 4	
 *
 * Purpose: Define the methods of a Set class
 *
 *****************************************************************************/
#include <iostream>
#include <cassert>

#include "Set.h"

using namespace std;

Set::Set(size_t capacity) {
  // The constructor. Creates a set with a maximum capacity of capacity
  //
  // PRE: None
  // POST: A set is created with the designated capacity
    
  Capacity = capacity; // Update the local variable Capacity
  Contents = new Item[Capacity]; // Allocate memory for the Set using 'new'
  ItemCount = 0; // Update the local variable ItemCount
 }

Set::Set(const Set& other){
   // The copy constructor. Creates a copy of a set
  //
  // PRE: None
  // POST: A copy of the set is created containing 
  //l of the original set's items

  copy(other); // Call the priavate method copy()
}

Set::~Set(){
  // The destructor
  //
  // PRE: None
  // POST: Destroys a set and frees up all allocated memory
  
  destroy(); // Call the private method destroy()
}

Set& Set::operator = (const Set& other){
  // The assignment operator. Ex: A = B
  //
  // PRE: None
  // POST: A contains all items of B and no others
    
   // assert(!(this == &other));assert not neccessary, use return

  if(this==&other) // Check to see if the sets are already equal 
    return *this;
    
  destroy(); // Destroy the memory allocated for the current set 
  copy(other); //  Reallocate memory for this set and copy other

  return *this;
}

void Set::insert(const Item& item){
  // Insert - inserts an item into the set.
  //
  // PRE: The set is not full
  // POST: The set contains just one instance of the the item.
    
  if(contains(item)) // Check to see if the item is already in the set
    return;
   
  assert(!full()); // Check to see if the Set is at max capacity
  
  Contents[ItemCount] = item; // Add the item to the Set
  ItemCount ++; // Update ItemCount
}

void Set::remove(const Item& item){ 
  // Remove - deletes an item from the set
  //
  // PRE: The set contains the item
  // POST: The set does not contain the item
  
  if(contains(item)) // If the item is in the set,
    for (size_t i = 0; i < ItemCount; i++) // loop through Contents.
      if (Contents[i] == item){ // If the item is found,
        Contents[i] = Contents[ItemCount-1]; // Overwrite the item.
        Contents[ItemCount-1] = 0; // Set index equal to the last in the set.

        // The two above lines are extremely efficient in that they remove the 
        // object by writing over it. The item that is moved there is the last one
        // in the set because this 'condenses' the set w/out shifting each item.
        // Lastly, we set the last item in the set equal to zero because now
        // there are two copies of it (in the new index and at the end).

        ItemCount--; // Update ItemCount

        return;}
}

bool Set::contains(const Item& item) const{
  // Contains - query whether a set contains an item
  // 
  // PRE: None
  // POST: Returns true if the set contains the item, false otherwise

  for (size_t i = 0; i < ItemCount; i++) // For each item in the set,
    if (Contents[i] == item) // if the item is found,
      return true; // return true.
  return false; // Return false otherwise.
}

size_t Set::cardinality() const{
  // cardinality - determines the number of items in the set
  //
  // PRE: None
  // POST: Returns the number of items in the set

  return ItemCount;
}

bool Set::empty() const{
  // empty - determines if the set is empty
  //
  // PRE: None
  // POST: Returns true if the set contains no items, false otherwise

  if (ItemCount == 0)
    return true;
  return false;
}

bool Set::full() const{
  // full - determines if the set is full
  //
  // PRE: None
  // POST: Returns true if the set has reached its capacity, flase otherwise

  return(ItemCount >= Capacity);
}

Set Set::setUnion(const Set& other) const{
  // union - forms the union of two sets
  //
  // PRE: None
  // POST: The returned set contains all items in boths sets

  Set temp(Capacity + other.Capacity); // Create a new set with enough capacity
  
  for (size_t i = 0; i < ItemCount; i++) // Copy  this set into temp
    temp.insert(Contents[i]);

  for (size_t i = 0;  i < other.ItemCount; i++) // For every item in other,
    if (!temp.contains(other.Contents[i])) // if it's not already in temp,
       temp.insert(other.Contents[i]); // add it to the temp set.

  return temp; // Return temp set 
}

Set Set::intersection(const Set& other) const{
  // intersection -forms the intersection of two sets 
  //
  // PRE: None
  // POST: The returned set contains only items in both sets

  Set temp(Capacity); // Create a new set that will be big enough 
  
  for (size_t i = 0;  i < ItemCount; i++) // For each item in this set,
    if (other.contains(Contents[i])) // if it is also in the other set,
      temp.insert(Contents[i]); // add it to the temp set.

  return temp; // Return temp set 

}

Set Set::difference(const Set& other) const{
  // difference - forms the set of items in this and not other
  //
  // PRE: None
  // POST: THe returned set contains items in this not in other

  Set temp(Capacity); // Create a new set that will be big enough 
  
  for (size_t i = 0; i < ItemCount; i++) // For each item in this set,
    if (!other.contains(Contents[i])) // if it is not in the other set,
      temp.insert(Contents[i]); // add it to the temp set.

  return temp; // Return temp set 
  } 

void Set::display(std::ostream& stream) const{
  // display - displays a set on a stream (output). Ex: {1, 2}
  //
  // PRE: None
  // POST: A printed representation sent to the stream

  // CITE: www.cplusplus.com/forum/beginner/22835/
  // DESC: Insight for how to begin this (use a loop)

  stream << "{";

  for (size_t i = 0; i < ItemCount; i++) // For each item in the set,
    if(i==0) 
      stream << Contents[i]; // Output the item
    else
      stream << ", " << Contents[i]; // Output the item

  // The above if statement handles formatting w/ commas.

  stream << "}";
}

void Set::copy(const Set& other){
  // A private method that creates a copy of the passed Set
  //
  // PRE: None
  // POST: A new set is created that contains all of the items of other

  // The following code creates a new Set using the information of other

  Capacity = other.Capacity; // Update the local variable Capacity
  Contents = new Item[Capacity]; // Allocate memory for the Set using 'new'
  ItemCount = other.ItemCount; // Update the local variable ItemCount

  for(size_t i = 0; i < ItemCount; i ++) // Copy other into this set
    Contents[i] = other.Contents[i];
}

void Set::destroy(){
  // A private method that destroys the Set that called it
  //
  // PRE: None
  // POST: The set is emptied and its pointer set to NULL

  // The following code is required when deleting space allocated with 'new'
  delete [] Contents;
  Contents = NULL;
}


