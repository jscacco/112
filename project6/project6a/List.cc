/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date: 11-1-17
 *
 * Assignment: Project 6A	
 *
 * Purpose: To implement a doubly linked list.
 *
 * File: List.cc
 *
 *****************************************************************************/
#include <iostream>
#include <cassert>
#include "List.h"

using namespace std;

typedef List::Node Node;
typedef List::Item Item;

// The Node constructor.
Node::Node(const Item& value, Node* next, Node* previous) {
  Value = value;
  Next = next; 
  Previous = previous;
}

// The Node copy constructor.
Node::Node(const Node& node) {
  Value = node.Value;
  Next = node.Next;
  Previous = node.Previous;
}

// The constructor.
// PRE: None.
// POST: A List is properly constructed.
List::List() {
  Current = NULL;
  Front = NULL;
  Rear = NULL;
  Length = 0;
}

// The copy constructor.
// PRE: None.
// POST: A new List is properly constructed containing the same objects and
// state as the List other.
List::List(const List& other) {
  copy(other);
}

// The destructor.
// PRE: None.
// POST: All memory allocated by the object is returned for reallocation.
List::~List() {
  destroy();
}

// The assignment operator.
// PRE: None.
// POST: The List other is copied to this List. All unnecessary memory is
// returned for reallocation.
List& List::operator =(const List& other) {
  // If they aren't already the same list:
  if(!(Front == other.Front)){
    destroy();
    copy(other);
  }
  return *this;
}
 
// insert - inserts an item into the list at the "current" location.
// PRE: None.
// POST: The item is inserted in the list before the "current" item. If
// "current" is at the end of the List, then the item is inserted at
// the end of the List. The "current" item is unchanged.
void List::insert(const Item& item) {
  // If the list is empty:
  if(!Front) {
    Front = new Node(item, NULL, NULL);
    Rear = Front;
  }
  // If Current points to the end of the list:
  else if(!Current) {
    Rear->Next =  new Node(item, NULL, Rear);
    Rear = Rear->Next;
  }
  // If Current points to the first Node:
  else if(!Current->Previous) {
    Front = new Node(item, Current, NULL);
    Current->Previous = Front;
  }
  // If Current points to the middle of the list:
  else {
     Current->Previous->Next =new Node(item, Current, Current->Previous);
     Current->Previous =  Current->Previous->Next;
  }

  Length++;
}

// remove - the current item is removed from the list.
// PRE: "current" is not at the end of the list.
// POST: The "current" item is removed from the list. "current" becomes the
// next item in the list, if possible, otherwise it becomes the item
// before the item being removed.
void List::remove() {
  assert(Current);
    
  // Create a temp pointer.
  Node* temp = Current;
  
  // Ensure a pointer points to the next node.
  if(Current->Previous) 
    Current->Previous->Next = Current->Next;
  else 
    Front = Current->Next;
    
  // Ensure a pointer points to the previous node.
  if(Current->Next)
    Current->Next->Previous = Current->Previous;
  else
    Rear = Current->Previous;
  
  // If you can, make Current point to the next node. 
  if(Current->Next) 
    Current = Current->Next;
  //Otherwise, set Current to the previous one.
  else
    Current = Current->Previous;

  // Delete the original Current.
  delete temp;
}

// begin - sets "current" to the beginning of the list.
// PRE: None.
// POST: "current" refers to the first item in the list.
void List::begin() {
  Current = Front;
  CurrentIndex = 0;
}

// current - returns the "current" item.
// PRE: "current" is not at the end of the list.
// POST: The "current" item is returned.
Item List::current() const {
  assert(Current);
  return Current->Value;
 }
 
// next - advances "current" to the next item in the list.
// PRE: "current" is not at the end of the list.
// POST: "current" not refers to the next item in the list.
void List::next() {
  assert(Current);
  Current = Current->Next;
  CurrentIndex++;
}

// atEnd - returns whether "current" refers to the end of the list.
// PRE: None.
// POST: returns true if "current" is at the end of the list, false otherwise.
 bool List::atEnd() const {
  return !Current;
}

// length - returns the number of items in the list.
// PRE: None.
// POST: The number of items in the list is returned (constant time).
size_t List::length() const {
  return Length;
}

// get - returns an item in the list by index.
// PRE: The List is not empty and index is less than the number of items in
// the List.
// POST: The desired item is returned.
Item List::get(size_t index) const {
  assert(Length!=0);
  assert(index>=0 && index < Length);

  // If current is already there, return the value.
  if(index==CurrentIndex)
    return Current->Value;
  // If the index precedes Current:
  else if(index < CurrentIndex){
    // If the index is closer to Current than the front:
    if(index>CurrentIndex/2) {
      // Start at current, move backward.
      Node* p = Current;
      for(size_t tempIndex = CurrentIndex; tempIndex != index; tempIndex--){
        p = p->Previous;
      }
      return p->Value;
    }
    // If the index is closer to the front than Current:
    else {
      // Start at front, move forwards.
      Node* p = Front;
      for(size_t tempIndex = 0; tempIndex != index; tempIndex++){
        p = p->Next;
      }
      return p->Value;
    }
  }
  // If index is after Current:
  else {
    // If the index is closer to Current than the rear:
    if(index<=(Length-1+CurrentIndex)/2){
      // Start at current, move forwards.
      Node* p = Current;
      for(size_t tempIndex = CurrentIndex; tempIndex != index; tempIndex++){
        p = p->Next;
      }
      return p->Value;
    }
    // If the index is closer to the rear tham Current:
    else {
      // Start at back, move backwards.
      Node* p = Rear;
      for(size_t tempIndex = Length-1; tempIndex != index; tempIndex--){
        p = p->Previous;
      }
      return p->Value;
    }
  }      
}

// display - displays a string version of the list on the stream.
// PRE: None.
// POST: A string version of the list has been sent to the stream. The
// format for lists is:
// "[]" for an empty list
// "[10]" for a single element list (with value 10)
// "[10, 15]" for multi-element lists.
void List::display(std::ostream& stream) const {
  stream << "[";

   for(Node* p = Front; p; p=p->Next) {
     if(p==Front)
       stream << p->Value;
     else
       stream << ", " << p->Value;
  }

   stream << "]";
}

// The special display method that shows where current
// is pointing and the value it points to.
void List::debugdisplay(std::ostream& stream) const {
  stream << "[";

  for(Node* p = Front; p; p=p->Next) {
    if(p==Front) {
      if(Current && Current == Front)
        stream << "*";
      stream << p->Value;
    }
    else{
      stream << ", ";
       if(Current && Current== p)
         stream << "*";
       stream << p->Value;
    }
  }

  if(!Current)
    stream << "*";
  stream << "]" << " (";

 
  if(!Current)
    stream << "end of list";
  else 
    stream << Current->Value;
  

  stream << ")" << endl;
}

// Creates a copy of a list starting at the passed node.
Node* List::copyNodes( Node* node,  Node* previous) {
  if(!node)
    return node;

  return new Node(node->Value, copyNodes(node->Next, node), previous);
}

void List::copy(const List& other) {
  // Set Length.
  Length = other.Length;
  
  // Copy the nodes and set Front.
  if(!other.Front) 
    Front = NULL;
  else 
    Front = copyNodes(other.Front, NULL);

  // Set Current.
  if(!other.Current){
    Current = NULL;
  }
  else {
    begin();
    for(size_t i = 0; i <other.CurrentIndex; i++) {
      next();
    }
  }
  
  // Set Rear.
  // While it isn't ideal to start at Front again, there is a segmentation 
  // fault if current is at the end of the list and we try to start there.
  if(!other.Rear)
    Rear = NULL;
  else {
    Rear = Front;
    while(Rear->Next) {
      Rear = Rear->Next;
    }
  }
}

// Deletes all nodes including and after the passed pointer.
void List::deleteNodes(Node* p) {
  if(p == NULL)
   return;

  deleteNodes(p->Next);
  delete p;
}

// Destroys the list by removing every node in it.
void List::destroy() {
  deleteNodes(Front);
}

// An output operator associated with the List. This simply calls display.
std::ostream& operator << (std::ostream& stream, const List& list) {
  list.display(stream);
  return stream;
}

// A special output operator associated with the List. This calls debugdisplay.
std::ostream& operator < (std::ostream& stream, const List& list) {
  list.debugdisplay(stream);
  return stream;
}
  
