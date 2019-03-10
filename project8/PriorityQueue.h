/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	12-18-17
 *
 * Assignment: Compression	
 *
 * File: PriorityQueue.h
 *
 * Purpose: To define the PriorityQueue class	
 *
 *****************************************************************************/
#ifndef __PQUEUE_H__
#define __PQUEUE_H__


class HuffmanTree {
 public:
  typedef unsigned char byte;

  // Purpose: Constructor
  //
  // Pre: None
  // Post: A Huffman tree is created
  HuffmanTree(byte value, size_t freq, HuffmanTree* left = NULL,
              HuffmanTree* right = NULL);

  // Purpose: Comparison operator (<)
  //
  // Pre: None
  // Post: If this tree's frequency is less than other's, return true,
  // otherwise return false.
  bool operator < (const HuffmanTree& other) const;

  byte Value;
  size_t Freq;
  HuffmanTree* Left;
  HuffmanTree* Right;
};

class PriorityQueue {
 public: 
  typedef HuffmanTree* ItemTy;

  // Purpose: Constructor
  //
  // Pre: None
  // Post: An empty priority queue of given capacity is created
  PriorityQueue(size_t capacity);

  // Purpose: Destructor
  //
  // Pre: None.
  // Post: All memory associated with the queue has been freed.
  ~PriorityQueue();

  // Purpose: Delete the HuffmanTree being pointed to.
  void destroy();

  // Purpose: Returns the number of items in the queue
  //
  // Pre: None.
  // Post: The number of items in the queue is returned.
  size_t length() const;

  // Purpose: Check if the "tree" is a heap
  //
  // Pre: None.
  // Post: If the tree is a heap, true is returned. Otherwise, false.
  bool isHeap(size_t tree = 0) const;

  // Purpose: Adds an item to the end of the queue
  //
  // Pre: The queue is not full.
  // Post: The item is inserted at the end of the queue.
  void enqueue(const ItemTy& item);

  // Purpose: Adds an item to the correct location in the queue
  //
  // Pre: The queue is not full.
  // Post: The item is inserted in the correct location
  void insert(const ItemTy& item);

  // Purpose: Return the parent of the given "Huffman Tree"
  size_t parent(size_t child) const;

  // Purpose: Return the left child of the given "Huffman Tree"
  size_t left(size_t root) const;

  // Purpose: Return the right child of the given "Huffman Tree"
  size_t right(size_t root) const;

  // Purpose: Removes an item from the front of the queue
  //
  // Pre: The queue is not empty.
  // Post: The front item in the queue is removed.
  void dequeue();
  
  // Purpose: Remove the first item from the queue and reorder.
  void remove();

  // Purpose: Reorder the queue after dequeueing
  void reheapDown();

  // Purpose: Inspect the front item in the queue.
  //
  // Pre: The queue is not empty.
  // Post: The item at the front of the queue is returned.
  ItemTy front() const;

  // Purpose: Determines if the queue is full
  //
  // Pre: None.
  // Post: If the queue contains the maximum capacity of items true is returned.
  // Otherwise, false.
  bool full() const;

  // Purpose: Determines if the queue is empty
  //
  // Pre: None.
  // Post: If the queue contains items, true is returned. Otherwise, false.
  bool empty() const;

  // Purpose: Determines if there is a node at the given array index
  // 
  // Pre: None.
  // Post: If there is a node there, true is returned. Otherwise, false.
  bool isThere(size_t index0) const;

  // Purpose: Reorders the queue after enqueueing
  // 
  // Pre: None.
  // Post: The items in the queue are in order.
  void reheapUp();

  // Purpose: Returns is the passed number is even
  bool isEven(size_t num) const;

  // Purpose: Display the queue in cout
  void display() const;


  ItemTy Queue[256];
  size_t Capacity;
  size_t Size;

};

#endif
