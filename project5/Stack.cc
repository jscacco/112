/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date: 10-14-17	
 *
 * Assignment: Project 5	
 *
 * File: Stack.cc
 *
 * Purpose: To create a stack of nodes that keeps track of the moves made
 *
 *****************************************************************************/
#include <cassert>
#include <iostream>
#include "Stack.h"

using namespace std;

// The type of element stored in the Stack
typedef Stack::Node Node;
typedef Stack::Item Item;

Node::Node(const Item& value, Node* next){
  Value = value;
  Next = next;
}

Node::~Node(){
}

// The constructor
// PRE: None
// POST: A stack is properly constructed
Stack::Stack(){
  Top = NULL;
}
  
// The copy constructor
// PRE: None
// POST: A stack is properly constructed with copies of elements from other
Stack::Stack(const Stack& other){
  copy(other);
}

// The destructor
// PRE: None
// POST: All memory associated with the stack is returned to the heap
Stack::~Stack(){
  destroy();
}
// The assignment operator
// PRE: None
// POST: All memory associated with the old stack contents is returned
//            to the heap. The other stack's contents is copied to this
//            stack.
Stack& Stack::operator = (const Stack& other){
  if (Top == other.Top)
    return *this;

  destroy();
  copy(other);
  return *this;
}
 
// push - a value is pushed onto the top of the stack
// PRE: None
// POST: A call to top() will return this element
void Stack::push(const Item& item){
   Top = new Node(item, Top);
 }
   
// pop - the top value is popped off the stack and discarded
// PRE: The stack is not empty
// POST: the top element of the stack has been removed
 void Stack::pop(){
   assert(!empty());
   Node* p = Top;
   Top = Top->Next;
   delete p;
 }

// top - get the top element of the stack
// PRE: the stack is not empty
// POST: the top element of the stack is returned
Stack::Item Stack::top() const{
   assert(!empty());
   return Top->Value;
 }

// empty - determines if the stack contains no elements
// PRE: None
// POST: true is returned if the stack has no elements, false otherwise
bool Stack::empty() const{
   return Top == NULL;
 }

// display - a string representation of the stack is sent to the stream
// PRE: None
// POST: a string representing the stack is sent to the stream.
//           Empty stack displays as:
//           <empty stack>
//           Non-empty stack displays as:
//           10 <- - - - - Top
//           5
//           3
//           <bottom>
void Stack::display(std::ostream& stream) const {
  if(empty())
    stream << "<empty stack>" << endl;
  else{
    Stack temp = *this;
    stream << temp.top() << " <------Top" << endl;
    temp.pop();
    while(!temp.empty()){
      stream << temp.top() << endl;
      temp.pop();
      
    }
    stream << "<bottom>" << endl;
  }
}

// The overloaded ouput operator
// PRE: None
// POST: The stack is displayed in the passed stream
std::ostream& operator <<(std::ostream& stream, const Stack& stack) {
  stack.display(stream);
  return stream;
}

// copyNode - copies the Nodes of other to this stack
// PRE: None
// POST: the nodes of other are now copied to this stack.
Node* Stack::copyNodes(const Node* node){
  if (node == NULL)
    return NULL;

  return new Node(node->Value, copyNodes(node->Next));
}

// copy - sets this stack to be a copy of other
// PRE: None
// POST: This stack is set to a copy of other
void Stack::copy(const Stack& other){
  Top =copyNodes(other.Top);
}

// destroy - destroys this stack
// PRE - None
// POST: This stack is destroyed and its memory returned to the heap.
void Stack::destroy(){
  while (!empty())
    pop();
}





