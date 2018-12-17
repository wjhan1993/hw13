#include "array.h"
#include <cstdio>
#include <iostream>
using namespace std;

class num{
public:
  num(int v){value = v;};
  num(){value = 0;};
  int getValue()const{return value;}
  friend ostream& operator<<(ostream& os,const num& output);
private:
  int value; 
};

ostream& operator<<(ostream& os,const num& output){
  cout << output.getValue();
  return os;
}

int main(int argc, char* argv[])
{

  num origin[10] = {num(-10),num(-8),num(-6),num(-4),num(-2),num(0),\
		    num(2),num(40),num(6),num(8)};
  
  Array<num> arr(8,origin);

  Array<num> rtoo(5,num(1));
 
  for(int i = 0; i < rtoo.size(); i++)
    rtoo[i] = num(i * 2);

  cout << "arr = " << arr << endl;
  cout << "rtoo = " << rtoo << endl; 

  
  Array<num> newArray;
  newArray = rtoo;
  
  cout << "newArray = " << newArray << endl;
  
  // append three integers to newArray 
  newArray.append(num(1));
  newArray.append(num(10));
  newArray.append(num(15));
  cout << "newArray size = " << newArray.size() << " and newArray =  " \
       << newArray;
  
  // copy constructor
  Array<num> newArraytoo(newArray);
  newArraytoo[0] = num(-100);
  cout << "newArraytoo = " << newArraytoo;

  // overload of +
  newArraytoo = newArray + arr;

  cout << "After adding, newArraytoo = newArray + arr :" << newArray << endl;
  
  // index out-bound
  for(int i = -2; i < arr.size(); i++)
    try{
      cout << " arr[" << i << "]" << " = " << arr[i];
    }
    catch(exception &e){
      cout << e.what() << endl;
    }
  
  return(0);
}

