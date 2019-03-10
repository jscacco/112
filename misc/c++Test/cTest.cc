/******************************************************************************
 *
 * Name:	Jack Scacco
 *
 * Date:	
 *
 * Assignment:	
 *
 * Purpose:	To mess around with c++
 *
 *****************************************************************************/
#include <iostream>
using namespace std;
void add(int a, int b){
  cout << "A value is: " << a << endl;
  cout << "B value is: " << b << endl;

  int c = a + b;
  cout << "Sum is: " << c << endl;
}

int main(){
  cout <<  "Hi! I'm C++!" << endl;
  int a = 11;
  int b = 211;
  add (a, b);
}
