/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	12-8-17
 *
 * Assignment: Compression	
 *
 * File: compress.cc
 *
 * Purpose: To either compress or uncompress a given file	
 *
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <stdlib.h>

using namespace std;

#include "PriorityQueue.h"

typedef HuffmanTree::byte byte;
typedef PriorityQueue::ItemTy ItemTy;

// CITE: https://stackoverflow.com/questions/5724171/
// passing-an-array-by-reference
// DESC: How to pass an array by reference.
void readCompressFile(char* file,  size_t& size, 
              size_t (&frequency)[256]) {
  // This method reads in the file to the string as 
  // well as calculates the frequencies
  fstream fin;
  byte b;
  fin.open(file);

  // For each character in the file:
  while(fin >> noskipws >> b) {
    // Add  it to the frequency array.
    frequency[b]++;
    // Update the size of the file
    size++;
  }
}

// Purpose: Set all frequencies in the array to 0.
void resetFrequency(size_t (&frequency)[256]) {
  // This method resets the frequency array.
  for (size_t i = 0; i < 256; i++) {
    frequency[i] = 0;
  }
  return;
}

// Purpose: Display the frequency array in cout.
void displayFrequency(size_t (&frequency)[256]) {
  cout << "Frequencies:" << endl;
  for (size_t i = 0; i < 256; i++) {
    cout << i << " : " << frequency[i] << endl;
  }
  return;
}

// Purpose: Create a new Huffman Tree pointer with passed values.
ItemTy createTree(size_t value, size_t frequency) {
  ItemTy temp = new HuffmanTree(value, frequency);
  return temp;
}

// Purpose: To add each value and its frequency to the queue
void fillQueue(PriorityQueue& queue, size_t (&frequency)[256]) {
  for (size_t i =0; i < 256; i++) {
    if (frequency[i] > 0) {
      ItemTy tree = createTree(i, frequency[i]);
      queue.insert(tree);
    }
  }
  return;
}

// Purpose: Return true if the passed tree is a Huffman Tree, false otherwise.
bool isHuffTree(ItemTy root) {
  assert(root != NULL);
  if (!root->Left)
    return !root->Right;
  else if (!root->Right)
    return false;
  else
    return root->Left->Freq + root->Right->Freq == root->Freq &&
      root->Left->Freq <= root->Right->Freq &&
      isHuffTree(root->Left) && isHuffTree(root->Right);
}

  
// Purpose: displays the tree to cout.
void displayTree(ItemTy tree, int depth = 0) {
  string s;
  if (!tree)
    return;

  displayTree(tree->Right, depth + 1);
  for(int i = 0; i < depth; i++)
    s+= "  ";
  cout << s << tree->Freq << ":" << tree->Value << endl;
  displayTree(tree->Left, depth + 1);
}

// Purpose: Create a single Huffman Tree from the Queue
ItemTy queueToTree(PriorityQueue& queue) {
  if (queue.empty())
    return NULL;
  if (queue.Size <= 1)
    return queue.front();
  else {
    ItemTy first = queue.front();
    assert(isHuffTree(first));
    queue.remove();

    ItemTy second = queue.front();
    assert(isHuffTree(second));
    queue.remove();

    size_t newFreq = first->Freq + second->Freq;
    // The '@' in the next line is just an arbitrary Value for interior nodes.
    ItemTy temp = new HuffmanTree('@', newFreq, first, second);
    assert(isHuffTree(temp));
    queue.insert(temp);

    return queueToTree(queue);
  }
}

// Purpose: Set all encodings to the empty string
void resetEncodings(string (&encodings)[256]) {
  // This method resets the frequency array.
  for (size_t i = 0; i < 256; i++) {
    encodings[i] = "";
  }
  return;
}

// Purpose: This method fills a mapping array with the 
// bit encodings of a HuffTree
void encodeBytes(string (&encodings)[256], ItemTy tree, string path = "") {
  if  (tree == NULL)
    return;
  if (!tree->Left)
    encodings[tree->Value] = path;
  else {
    encodeBytes(encodings, tree->Left, path + "0");
    encodeBytes(encodings, tree->Right, path + "1");
  }
  return;
}

// Purpose: Display the encoding array in cout.
void displayEncodings(string (&encodings)[256]) {
  cout << "Encodings:" << endl;
  for (size_t i = 0; i < 256; i++) {
    cout << i << " : " << encodings[i] << endl;
  }
  return;
}

byte bitsToByte(string bits) { // ***NOT SURE THIS WORKS***
  // This method takes a string of eight 1's and 0's and 
  // returns the corresponding byte.
  assert(bits.length() == 8);
  byte result = 0;
  for (size_t i = 0; i < 8; i++) {
    result <<= 1;  
    if (bits[i] == '1')
      result ++;
  }
  return result;
}

// Purpose: Represent a Huffman Tree as a string
void encodeTree(ItemTy tree, string& encoding) {
  if (!tree)
    return;
  if (!tree->Left) {
    encoding += 'L';
    encoding += tree->Value;
  }
  else
    encoding +=  'I';
  encodeTree(tree->Left, encoding);
  encodeTree(tree->Right, encoding);
  return;
}

// Purpose: Fill a bit string with 0's until it has a length of 8
string fillBitString(string bits) {
  assert(bits.length() < 8);
  while (bits.length() < 8) {
    bits += '0';
  }
  return bits;
}

// Purpose: Check if there are enough characters in the bank to output a compressed character
void checkBitBank(string& bank) {
    if (bank.length() >= 8) {
    byte temp = bitsToByte(bank.substr(0,8));
    cout << temp;
    bank = bank.substr(8);
  }
  return;
}

// Purpose: create and output the new bytes from the binary strings
void compressText(char* file, byte size,  string encodings[256]) {
  fstream fin;
  fin.open(file);
  byte temp;
  string BitBank = "";
  while (fin >> noskipws >> temp) {
    BitBank += encodings[temp];
    checkBitBank(BitBank);
  }
  while (BitBank.length() > 0) {
    if (BitBank.length() < 8)
      BitBank = fillBitString(BitBank);
    checkBitBank(BitBank);
  }
  assert(BitBank.length() == 0);
  return;
}

// Purpose: Synthesize all of the compressions methods and compress a file
void compressFile(char* File) {
   // Create a string to store the file
  string Text;
  // Create an unsigned integer to store the file size
  size_t Size = 0;
  // Create an array to store the frequencies
  size_t Frequency[256];
  resetFrequency(Frequency);
  // Create a Huffman Tree pointer that will store the characters
  ItemTy MapTree;
  // Create a Priority Queue to create the tree
  PriorityQueue Queue(256);
  // Create an array to store the bit encodings of the tree
  string Encodings[256];
  // Create a string to store the encoding of the tree
  string TreeEncoding = "";
  
  readCompressFile(File, Size, Frequency);
  // displayFrequency(Frequency);
  fillQueue(Queue, Frequency);
  //Queue.display();
  MapTree = queueToTree(Queue);
  // displayTree(MapTree);
  encodeBytes(Encodings, MapTree);
  //displayEncodings(Encodings);
  encodeTree(MapTree, TreeEncoding);
  cout << Size;
  cout << TreeEncoding;
  compressText(File, Size, Encodings);
  
  return;
}


// Purpose: Read the next byte in the file
byte readNextByte() {
  byte b;
  cin >> noskipws >> b;
  return  b;
}

// Purpose: Build a tree from its string representation
ItemTy buildTree(byte currentFirst) {
  if (currentFirst == 'L') {
    currentFirst = readNextByte();
    return new HuffmanTree(currentFirst, 0);
  }
  else if (currentFirst == 'I') {
    return new HuffmanTree('@', 0, buildTree(readNextByte()), buildTree(readNextByte()));
  }
  else 
    return NULL;
}

// Purpose: Get the first byte of a compressed file size
void getFileSize(size_t& size, byte& currentFirst,  string strSize = "") {
  byte firstByte;
  firstByte = readNextByte();
  
  if (firstByte == 'I' || firstByte == 'L') {
    // CITE: http://www.cplusplus.com/forum/articles/9645/
    // DESC: How to convert a string to an int.
    size_t temp;
    stringstream convert(strSize);
    // Update the passed Size
    size = convert >> temp ? temp : 0;
    // Keep track of the most recent firstByte
    currentFirst = firstByte;
  }
  else {
    strSize += firstByte;
    getFileSize(size, currentFirst, strSize);
  }
  
}

// Purpose: Convert a byte to a string of bits
string byteToBits (byte b) {
  string result = "";
  for (int i = 0; i < 8; i++) {
    if (b % 2 == 1)
      result = "1" + result;
    else
      result = "0" + result;
    b >>= 1;
  }
  return result;
}

// Purpose: Traverse the file/tree and  output the results
void uncompressText(size_t Size, ItemTy Tree) {
  byte Temp = readNextByte();
  string BitBank = byteToBits(Temp);
  ItemTy Root = Tree;
  size_t Counter = 0;

  while (Counter < Size) {
    if (!Tree)
      Tree = Root;
    else if (!Tree->Left) {
      cout << Tree->Value;
      Tree = Root;
      Counter ++;
    }
    else if (BitBank[0] == '0') {
      BitBank = BitBank.substr(1);
      Tree = Tree->Left;
    }
    else if (BitBank[0] == '1') {
      BitBank = BitBank.substr(1);
      Tree = Tree->Right;
    }

    if (BitBank.length() == 0) {
      Temp = readNextByte();
      BitBank += byteToBits(Temp);
    }
  }

  return;
}

// Purpose: Uncompress a file
void uncompressFile() {
  size_t Size;
  byte CurrentFirst;
  ItemTy Tree;

  getFileSize(Size, CurrentFirst);
  Tree = buildTree(CurrentFirst);
    uncompressText(Size, Tree);
  return;
}


int main(int argc, char* argv[]) {
  
  string term = argv[0];
  if (term == "uncompress" || (term.length() >= 10 && 
                               term.substr(term.length() - 10) == "uncompress"))

    uncompressFile();
  else {
    char* File;
    assert(argc >=2);
    File = argv[1];
    compressFile(File);
  }
  

    return 0;
}


