/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	12-8-17
 *
 * Assignment: Compression	
 *
 * File: PriorityQueue.cc
 *
 * Purpose: To implement the PriorityQueue class
 *
 *****************************************************************************/
#include <iostream>
#include <cassert>

using namespace std;

#include "PriorityQueue.h"

typedef HuffmanTree* ItemTy;
typedef unsigned char byte;

// Purpose: Constructor
//
// Pre: None
// Post: A Huffman tree is created
HuffmanTree::HuffmanTree(byte value, size_t freq, HuffmanTree* left,
                         HuffmanTree* right) {
  Value = value;
  Freq = freq;
  Left = left;
  Right = right;
}

// Purpose: Comparison operator (<)
// Pre: None
// Post: If this tree's frequency is less than other's, return true,
// otherwise return false.
bool HuffmanTree::operator < (const HuffmanTree& other) const {
  return Freq < other.Freq;
}

 // Purpose: Constructor
 //
 // Pre: None
 // Post: An empty priority queue of given capacity is created
 PriorityQueue::PriorityQueue(size_t capacity) {
   Capacity = capacity;
   Size = 0;
 }

 // Purpose: Destructor
 //
 // Pre: None.
 // Post: All memory associated with the queue has been freed.
 PriorityQueue::~PriorityQueue() {
   for (size_t i = 0; i < Capacity; i++) {
     return;
   }
 }

 // Purpose: Returns the number of items in the queue
 //
 // Pre: None.
 // Post: The number of items in the queue is returned.
 size_t PriorityQueue::length() const {
   return Size;
 }

// Purpose: Check if the "tree" is a heap
//
// Pre: None.
// Post: If the tree is a heap, true is returned. Otherwise, false.
bool PriorityQueue::isHeap(size_t tree) const {
  if (! isThere(tree))
    return true;
  else if (isThere(parent(tree)) && *Queue[tree] < *Queue[parent(tree)])
    return false;
  else 
    return isHeap(left(tree)) && isHeap(right(tree));
}

 // Purpose: Adds an item to the end of the queue
 //
 // Pre: The queue is not full.
 // Post: The item is inserted at the end of the queue.
 void PriorityQueue::enqueue(const ItemTy& item) {
   Queue[Size] = item;
   Size++;
   return;
 }

 // Purpose: Adds an item to the correct location in the queue
 //
 // Pre: The queue is not full.
 // Post: The item is inserted in the correct location
 void PriorityQueue::insert(const ItemTy& item) {
   assert(Size != Capacity);
   enqueue(item);
   reheapUp();
   assert(isHeap());
   return;
 }

 // Purpose: Reorders the queue after enqueueing
 // 
 // Pre: None.
 // Post: The items in the queue are in order.
 void PriorityQueue::reheapUp() {
   size_t current = Size - 1;
   size_t compare = parent(current);
   
   while(isThere(compare)) {
     if (*Queue[current] < *Queue[compare]) {
       // Switch the two
       HuffmanTree* temp = Queue[current];
       Queue[current] = Queue[compare];
       Queue[compare] = temp;
     }
     else
       return;
     
     // Update the current and compare values.
     current = compare;
     compare = parent(current);
   }
  return;
}

// Purpose: Return the parent of the given "Huffman Tree"
size_t PriorityQueue::parent(size_t child) const {
  size_t temp = child;
  if (isEven(temp))
    temp -= 2;
  else
    temp--;
  temp /= 2;   
  return temp;
}

// Purpose: Return the left child of the given "Huffman Tree"
size_t PriorityQueue::left(size_t root) const {
  size_t temp = root * 2 +1;
  // assert(isThere(temp));
  return temp;
}

// Purpose: Return the right child of the given "Huffman Tree"
size_t PriorityQueue::right(size_t root) const {
    size_t temp = root * 2 + 2;
    // assert(isThere(temp));
    return temp;
}

bool PriorityQueue::isEven(size_t num) const {
  return num % 2 == 0;
}

// Purpose: Removes an item from the front of the queue
//
// Pre: The queue is not empty.
// Post: The front item in the queue is removed.
void PriorityQueue::dequeue() {
  // Bring the most recent to the front
  Queue[0] = Queue[Size - 1];
  Queue[Size] = NULL;
  Size--;
  return;
}

// Purpose: Remove the first item from the queue and reorder.
void PriorityQueue::remove() {
  assert(Size != 0);
  dequeue();
  reheapDown();
  assert(isHeap());
  return;
}
// Purpose: Reorder the queue after dequeueing
void PriorityQueue::reheapDown() {
  size_t current = 0;
  size_t leftChild = left(current);
  size_t rightChild = right(current);

  while (isThere(current) && isThere(leftChild)) {
    // If the right child is there and is smaller than its parent and sibling:
    if (isThere(rightChild) && *Queue[rightChild] < *Queue[current] &&
        !(*Queue[leftChild] < *Queue[rightChild])) {
      // Switch the right child and the parent
      HuffmanTree* temp = Queue[current];
      Queue[current] = Queue[rightChild];
      Queue[rightChild] = temp;
      current = rightChild;
    }
    // If the left child is smaller than the parent:
    else if (*Queue[leftChild] < *Queue[current]) {
      // Switch the left child and the parent
      HuffmanTree* temp = Queue[current];
      Queue[current] = Queue[leftChild];
      Queue[leftChild] = temp;
      current = leftChild;
    }
      
    // Otherwise, we can't switch the current with anything.
    else 
      return;

    leftChild = left(current);
    rightChild = right(current);
  } 
  return;
}
        

// Purpose: Inspect the front item in the queue.
//
// Pre: The queue is not empty.
// Post: The item at the front of the queue is returned.
ItemTy PriorityQueue::front() const {
  assert (Size !=0);
  return Queue[0];
}

// Purpose: Determines if the queue is full
//
// Pre: None.
// Post: If the queue contains the maximum capacity of items true is returned.
// Otherwise, false.
bool PriorityQueue::full() const {
  return Size == Capacity;
}

// Purpose: Determines if the queue is empty
//
// Pre: None.
// Post: If the queue contains items, true is returned. Otherwise, false.
bool PriorityQueue::empty() const {
  return Size == 0;
}

// Purpose: Determines if there is a node at the given array index
// 
// Pre: None.
// Post: If there is a node there, true is returned. Otherwise, false.
bool PriorityQueue::isThere(size_t index) const {
  return index < Size && index >= 0;
}

// Purpose: Display the queue in cout
void PriorityQueue::display() const {
    for (size_t i = 0; i < Size; i++) {
    cout << "Value: " << Queue[i] ->Value << "; Frequency: " 
      << Queue[i]->Freq << endl;
  }
  return;
}
