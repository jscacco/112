/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	10-24-17
 *
 * Assignment: Project 5
 *
 * File: Stack.h
 *
 * Purpose: To declare the methods that will be used in Stack.cc
 *
 *****************************************************************************/
#ifndef STACK_H
#define STACK_H

class Stack {
 public:
   // The type of element stored in the Stack
  typedef int Item;

  // The type of object that contains the information. I'm not commenting
  // its functions because it is a commonly used object.
  class Node{
  public:
    Node(const Item& value, Node* next = NULL);
    ~Node();
    Item Value;
    Node* Next;
  private:
    Node(const Node* node);
    Node& operator = (const Node& node);
  };

  // The constructor
  // PRE: None
  // POST: A stack is properly constructed
  Stack();
  
  // The copy constructor
  // PRE: None
  // POST: A stack is properly constructed with copies of elements from other
  Stack(const Stack& other);

  // The destructor
  // PRE: None
  // POST: All memory associated with the stack is returned to the heap
  ~Stack();

  // The assignment operator
  // PRE: None
  // POST: All memory associated with the old stack contents is returned
  //            to the heap. The other stack's contents is copied to this
  //            stack.
  Stack& operator = (const Stack& other);

  // push - a value is pushed onto the top of the stack
  // PRE: None
  // POST: A call to top() will return this element
  void push(const Item& item);

  // pop - the top value is popped off the stack and discarded
  // PRE: The stack is not empty
  // POST: the top element of the stack has been removed
  void pop();

  // top - get the top element of the stack
  // PRE: the stack is not empty
  // POST: the top element of the stack is returned
  Item top() const;

  // empty - determines if the stack contains no elements
  // PRE: None
  // POST: true is returned if the stack has no elements, false otherwise
  bool empty() const;

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
  void display(std::ostream& stream) const;

 private:
  // copy - copies other to this stack
  // PRE: None
  // POST: This stack is a copy of the other
  void copy(const Stack& other);
  
  // destroy - destroys this stack
  // PRE - None
  // POST: This stack is destroyed and its memory returned to the heap.
  void destroy();

  // copyNode - copies the Nodes of other to this stack
  // PRE: None
  // POST: the nodes of other are now copied to this stack.
  Node* copyNodes(const Node* node);

   //The pointer to the linked Nodes
  Node* Top;
};

std::ostream& operator <<(std::ostream& stream, const Stack& stack);

#endif
