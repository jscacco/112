/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	
 *
 * Assignment:	
 *
 * Purpose:    Bag class Header file
 *
 *****************************************************************************/

#ifndef BAG_H
#define BAG_H

class Bag{
 public:
  typedef int Item;
  Bag();
   
  void putIn(Item value);
  bool lookIn(Item value) const;
  void takeOut(Item value);
  void dumpOut();

 private:
  Item Contents[100];
  int ItemCount
};

#endif 
