/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	
 *
 * Assignment:	
 *
 * Purpose:   The file that actually contains the bag
 *
 *****************************************************************************/
#include <iostream>
#include <cassert>

#include "Bag.h"

using namespace std;

Bag::Bag(){
  Contents = new Item[100]
}
   
  void putIn(Item value);
  bool lookIn(Item value) const;
  void takeOut(Item value);
  void dumpOut();
