/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	11-1-17
 *
 * Assignment: Project 6A
 *
 * Purpose: To declare a doubly linked list class
 *
 * File: List.h
 *
 *****************************************************************************/
#ifndef LIST_H
#define LIST_H

#include <iostream>

class List {
 public:
  typedef int Item; // The type of items you can store in a List

  // The constructor.
  // PRE: None.
  // POST: A List is properly constructed
  List();

  // The copy constructor.
  // PRE: None.
  // POST: A new List is properly constructed containing the same objects and
  // state as the List other.
  List(const List& other);

  // The destructor
  // PRE: None.
  // POST: All memory allocated by the object is returned for reallocation.
  ~List();

  // The assignment operator
  // PRE: None.
  // POST: The List other is copied to this List. All unnecessary memory is
  // returned for reallocation.
  List& operator =(const List& other);

  // insert - inserts an item into the list at the "current" location
  // PRE: None.
  // POST: The item is inserted in the list before the "current" item. If
  // "current" is at the end of the List, then the item is inserted at
  // the end of the List. The "current" item is unchanged.
  void insert(const Item& item);

  // remove - the current item is removed from the list.
  // PRE: "current" is not at the end of the list.
  // POST: The "current" item is removed from the list. "current" becomes the
  // next item in the list, if possible, otherwise it becomes the item
  // before the item being removed.
  void remove();

  // begin - sets "current" to the beginning of the list
  // PRE: None.
  // POST: "current" refers to the first item in the list.
  void begin();

  // current - returns the "current" item
  // PRE: "current" is not at the end of the list
  // POST: The "current" item is returned
  Item current() const;

  // next - advances "current" to the next item in the list.
  // PRE: "current" is not at the end of the list
  // POST: "current" not refers to the next item in the list.
  void next();

  // atEnd - returns whether "current" refers to the end of the list
  // PRE: None.
  // POST: returns true if "current" is at the end of the list, false otherwise.
  bool atEnd() const;

  // length - returns the number of items in the list
  // PRE: None.
  // POST: The number of items in the list is returned (constant time).
  size_t length() const;

  // get - returns an item in the list by index
  // PRE: The List is not empty and index is less than the number of items in
  // the List.
  // POST: The desired item is returned.
  Item get(size_t index) const;

  // display - displays a string version of the list on the stream
  // PRE: None.
  // POST: A string version of the list has been sent to the stream. The
  //        format for lists is:
  //        "[]" for an empty list
  //        "[10]" for a single element list (with value 10)
  //        "[10, 15]" for multi-element lists.
  void display(std::ostream& stream) const;

  void debugdisplay(std::ostream& stream) const;

 // The typical Node class, with an added 'Previous" pointer
 // I am not going to describe each method since they are quite standard
  class Node {
  public:
    Node(const Item& value, Node* next, Node* previous);
    Item Value;
    Node* Next;
    Node* Previous;
  private:
    Node(const Node& node);
    Node& operator = (const Node& node);
  };

 private:
  void copy(const List& other);
  void deleteNodes(Node* p);
  Node*  copyNodes(Node* current, Node* previous);
  void destroy();
  Node* Current;
  Node* Front;
  Node* Rear;
  size_t CurrentIndex;
  size_t Length;
};

// An output operator associated with the List. This simply calls display.
std::ostream& operator << (std::ostream& stream, const List& list);

// A special output operator associated with the List. This calls debugdisplay.
std::ostream& operator < (std::ostream& stream, const List& list);

#endif
