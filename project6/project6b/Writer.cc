/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	11-5-17
 *
 * Assignment: Project 6B	
 *
 * Purpose: To create a Frequent Writer program
 *
 *File: writer.cc
 *
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <cassert>
// CITE: http://www.cplusplus.com/reference/cstdlib/atoi/
// DESC: Information pertaining to the atoi function
#include <stdlib.h>
#include <cs112.h>

using namespace std;

#include "List.h"

typedef List::List List;

// readCorpus - returns the list of characters that compose the corpus.
// PRE:  None,
// POST: Each character from the passed test file is placed into a list
// in order. 
void readCorpus(const char* text, List& corpus) {
  char c;

  // CITE: C++ Plus Data Structures, 6th Edition
  // DESC: How to use fstream to input
  ifstream fin;
  fin.open(text);
 
  corpus.begin();

  // Read each character in the file into corpus.
  while(fin >> noskipws >> c){
    corpus.insert(c);
  }
}

// initializePrefix - creates the first prefix.
// PRE: Prefix list is empty.
// POST: The first [prefixLength] characters of the corpus 
// are added to a list and printed.
void readFirstPrefix(List corpus, List& list, const int length) {
  assert(list.length() == 0);
  
  // Insert the first [length] characters of the corpus into the prefix list
  // and print them out.
  for(int i = 0; i < length; i++) {
    list.insert(corpus.get(i));
    cout << corpus.get(i);
  }
}

// shiftPrefix - builds a new lsit based on a passed list and suffix.
// PRE: None.
// POST: The first letter of the old prefix is removed 
// and the suffix added to the end.
void shiftList(List& list, const char newchar) {
  // Move to the front and remove the first item.
  list.begin();
  list.remove();
  
  // Move to the end of the list and remove the last item.
  while (!list.atEnd()) {
    list.next();
  }
  list.insert(newchar);
}

// getSuffixes - creates a list of new suffixes.
// PRE: None.
// POST: A list full of characters that follow the passed prefix is added to a list.
void getSuffixes(List& corpus, List& suffixes, const List prefix) {
  // Reset suffixes.
  List blank;
  suffixes = blank;
  
  List minicorpus;
  // Set minicorpus equal to the initial prefix length frame of corpus.
  corpus.begin();
  for(size_t i = 0; i < prefix.length(); i++) {
    minicorpus.insert(corpus.current());
    corpus.next();
  }
  
  // Go through corpus and look at every possible prefix.
  for(size_t cindex = prefix.length(); 
      cindex < corpus.length(); cindex++) {
    
    // If minicorpus is the  same as the actual prefix, add the
    // next character to suffixes list.
    if(minicorpus == prefix)
      suffixes.insert(corpus.current());

    // Move to the next minicorpus
    shiftList(minicorpus, corpus.current());
    corpus.next();
  }
}

// chooseSuffix - returns a random suffix.
// PRE: The list is not empty.
// POST: A random character from the passed list is returned.
char chooseSuffix(const List suffixes) {
  assert(suffixes.length() > 0);

  // Generate a random index.
  size_t index = cs112::random(suffixes.length());

  return suffixes.get(index);
 }


// generate - outputs a string based off of the passed corpus.
// PRE: the corpus is not less than the prefix length.
// POST: Randomly generated text is output
void generate(List corpus, const int prefixLength, 
              const int textLength) {
  // Set the initial prefix and output it.
  List prefix;
  readFirstPrefix(corpus, prefix, prefixLength);
  prefix.begin();
  
  // Create a character counter that keeps track of how many characters
  // have been output.
  int characterCount = prefix.length();

  // Create a suffixes list to be used.
  List suffixes;

  // Create a suffix char to be used.
  char suffix;

  // Do this until we satisfy the text length.
  while (characterCount  < textLength) {
    // Get all of the suffixes and put them into suffixes.
    getSuffixes(corpus, suffixes, prefix);
        
    // If there are no suffixes, end the generation process.
    if(suffixes.length() == 0) {
      cout << endl;
      return;
    }
  
    // Choose a suffix and store it in suffix.
    suffix = chooseSuffix(suffixes);
    
    // Output the suffix and adjust the counter.
     cout << suffix;
    characterCount ++;

    // Build a new prefix using the chosen suffix.
    shiftList(prefix, suffix);
  }

  cout << endl;
  return;
}

int main(int argc, char* argv[]){
  size_t PrefixLength  = atoi(argv[1]);
  size_t TextLength =atoi(argv[2]);
  List Corpus;
  readCorpus(argv[3], Corpus);
     
  // If the corpus is at least as long as the prefix length:
  // (Prevents bounds errors).
  if(Corpus.length() >= PrefixLength) {
    generate(Corpus, PrefixLength, TextLength);
 }
  
  return 0;
}
