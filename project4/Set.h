/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	10-9-17
 *
 * File: Set.h
 *
 * Assignment: Project 4	
 *
 * Purpose: Define the methods and objects of the Set class
 *
 *****************************************************************************/
#ifndef SET_H
#define Set_H

class Set {
 public:
  typedef int Item; // The object that will be stored in the Set (essentially an int)
  Set(size_t capacity = 100); // The constructor
  Set(const Set& other); // The copy constructor
  ~Set(); // The desctructor
  Set& operator = (const Set& other); // Assignment operator
  void insert(const Item& item); // Insert - inserts an item into the set.
  void remove(const Item& item); // Remove - removes an item from the set.
  bool contains(const Item& item) const; // Contains - checks to see
                                                                  //if the set contains an item
  size_t cardinality() const; // cardinality - determines the number of items in the set
  bool empty() const; // empty - returns true if the set is empty
  bool full() const; // full - returns true if the set is full
  Set setUnion(const Set& other) const; // union - forms the union of two sets
  Set intersection(const Set& other) const; // intersection - forms the intersection of two 
                                                                      //sets (the set of items contained in both)
  Set difference(const Set& other) const; // difference - forms the set of items in this 
                                                                   //and not other
  void display(std::ostream& stream) const;
 private:
  Item* Contents; //A pointer to an array of Items
  size_t Capacity; // A size_t to keep track of how large the Sets may become
  size_t ItemCount; // A size_t to keep track of how many Items are in the Set
  void copy(const Set& other); // A method to create a copy of the passed Set
  void destroy();  // A method to destroy the Set that calls it
};

#endif
