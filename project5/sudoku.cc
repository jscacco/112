/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date: 10-24-17	
 *
 * Assignment:Project 5	
 *
 * File: sudoku.cc
 *
 * Purpose: To create a file that solves a sudoku puzzle
 *
 *****************************************************************************/
#include <iostream>
#include <cassert>
#include <SudokuBoard.h>
#include "Stack.h"

using namespace std;

typedef Stack::Node Node;
typedef Stack::Item Item;
typedef cs112::SudokuBoard Board;

bool canPlace(const Board& board,  size_t& row,  size_t& col, size_t& value){
  // This method checks to see if a value can be placed in a certain location.

  for(size_t i = 0; i < board.BoardSize; i++){
    // Check vertically for conflicts.
    if(!board.empty(i, col))
       if(board.get(i, col) == value)
         return false;
    
    // Check horizontally for conflicts.
    if(!board.empty(row, i))
       if(board.get(row, i) == value)
         return false;
  }

  //Check the smaller square for conflicts
  size_t baseRow = (row/3)*3; // These 3s are used because that is the 
  size_t baseCol = (col/3)*3; // dimension of the smaller square.
  for(size_t r = baseRow; r < baseRow + 3; r++)
    for(size_t c = baseCol; c < baseCol + 3; c++)
      if(!board.empty(r, c))
        if(board.get(r, c) == value)
          return false;

  // If there are no conflicts, we can place the number.
  return true;
}

bool mostConstrained(const Board& board, size_t& row, size_t& col){
   // This method looks for the most constrained spot in the board.
  // If there are no moves that can possibly be made, false is returned.
  // Otherwise, true is returned and the passed row and col are updated
  // to be the most constrained spot.

  // Nothing can have a value higher than 10, so it is 'out of bounds'.
  size_t valueCounter = 10;

  // Check every position
  for(size_t r=0; r < board.BoardSize; r++)
    for(size_t c=0; c < board.BoardSize; c++)
      // If there isn't a value already there,
      if(board.empty(r, c)){
          // check how many values could go there.
          size_t tempCount = 0;
          for(size_t val = 1; val <= board.BoardSize; val++)
            if(canPlace(board, r, c, val))
              tempCount ++;
          // If this spot is more constrained than those already tested,
          if(tempCount < valueCounter){
            // set the row and col to this position.
            row = r;
            col = c;
            valueCounter = tempCount;
            // Since 1 is the most constrained possible, return if we have it.
            if(valueCounter == 1)
              return true;
          }
      }
  // If values could actually go here, return true.
  if(valueCounter > 0 && valueCounter < 10)
    return true;
  
  // Otherwise, we cannot place any things.
  return false;
}
  
void makeMove(Board& board, Stack& stack, const size_t row, 
              const size_t col, const size_t value){
  // This method stores the location of the move in the passed stack
  // and places the passed value at that location
  
  // Store the row and col in the stack for later use.
  stack.push(row);
  stack.push(col);

  // Put the value into the board.
  board.put(value, row, col);
}

void undoMove(Board& board, Stack& stack, size_t& row, 
              size_t& col, size_t& value){
  // This method 'undoes' the last move by popping it out 
  // of the stack and clearing that spot.
  // It sets the passed row and col equal to the position of the last move.
  
  //Remove the col and the row from the stack and store them.
  col = stack.top();
  stack.pop();
  row = stack.top();
  stack.pop();
  
  // Store the value in the board and then clear the board
  value = board.get(row, col);
  board.clear(row, col);
}

bool nextValue(Board& board, size_t row,  size_t col, size_t& value){
  // This method returns true if there is a value starting 
  // at the inputed value  that can be placed in the passed space.
  // It then sets value equal to that new value.
  // It returns false if nothing after the passed value can be
  // placed in the spot.

  // For each value,
  for(size_t val = value; val <= board.BoardSize; val++){
    // Check if you can place the value.
    if(canPlace(board, row, col, val)){
      // If you can place it, modify the passed value and return true.
      value = val;
      return true;
    }
  }
  
  // If you cannot place any value, return false.
  return false;
}

bool backtrack(Board& board, Stack& stack){
   // This method undoes the last move and tries the 
  // same spot with the next possible value.
  // If no value after the tested one works, return true.
  // If one of them does work, return false.

  // Create some local variables.
  size_t row = 0;
  size_t col = 0;
  size_t value = 0;

  // Undo the move and increase the val so we can check
  // all of the values after that one.
  undoMove(board, stack, row, col, value);
  value++;

  // If there is a value after the previous that we can place here,
  if(nextValue(board, row, col, value)){
    // Make that move and return false.
    makeMove(board, stack, row, col, value);
    return false;
  }
  
  // If we cannot place any other values here, return true.
  return true;
}

bool solve(Board& board){
  // This method uses all the others to actually solve the puzzle
  
  // Create a stack that will store all of the moves.
  Stack moves;
  
  // While there are empty spaces on the board, 
  while(board.emptySpaces() > 0){
    // Create some local variables.
    size_t row = 0;
    size_t col = 0;
    size_t value = 1;
    
    // If there is a spot that is empty, find the most constrained one.
    if(mostConstrained(board, row, col)){
      // If there is a value we can put there, find the first one.
      if(nextValue(board, row, col, value)){
        // Make the move using the next value in the most constrained square.
        makeMove(board, moves, row, col, value);
      }
      // If there is no next value,
      else{
        // while we can keep backtracking,
        do {
          // return false if there are no moves in the stack.
          if(moves.empty())
            return false;
          value ++;
          // Backtrack and try again with an incremented value.
        } while(backtrack(board, moves));
      }
    }
    else {
      do{
        if(moves.empty())
          return false;
        value ++;
      } while(backtrack(board, moves));
    }
  }

  // If we get through the entire loop, return true because
  // the board has been solved.
  return true;
}

int main(){
  // The main method.
  //Input the sudoku board that needs to be solved
  Board board;
  cin >> board;

  // If we can solve the board, display it.
  if(solve(board)){
    cout << board;
  }
  // If we can't, display 'Unsolvable'.
  else
    cout << "There is no solution" << endl << board;
  }
