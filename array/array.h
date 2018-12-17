#ifndef ARRAY_H_INCLUDED_
#define ARRAY_H_INCLUDED_
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <new>
using namespace std;

class OutOfBoundsException: public exception
{
  virtual const char* what() const throw()
  {
    return "Out of Bounds happened!";
  }
}myError;

template<class myType>
class Array{
public:
  // Default constructor
  Array();

  // Array(int length,myType* value)
  Array(int length, myType* value);
  
  // copy constructor
  Array(const Array& y);

  // Destructor
  ~Array();

  // Initialize an array with size =s and assign all elements as v
  Array(int s, myType v);

  // get size
  int size() const;

  // append x to the end of the array
  void append(myType x);

  // append array y to the end of the array
  void append(const Array& y);

  // overload of =
  Array& operator=(const Array& y);
 
  // overload of []
  myType& operator[](int index)const;

  // overload of <<
  template<class Y>
  friend ostream& operator<<(ostream& os, const Array<Y>& y);  

  // get capacity
  int getCapacity()const;

  // overload of +
  Array& operator+(const Array& y);

  // release all memeory, called by the destructor 
  void cleanup();
  
private:
    // array stores all elements
    myType* array;

    // size is the capacity of the array
    int Size;

    // count records the number of elements in the current array 
    int capacity;

    // double the arraysize when the array is full
    void expand();
};

// Constructor
template <class myType>
Array<myType>::Array(){
  
  try
  {
    array = new myType[2];
  }
  catch(const exception &e){
    cout << "new exception " <<  e.what() << endl;
  }
  
  if (array != NULL){
    Size = 0;
    capacity  = 2;
  }
  
}

// copy constructor
template <class myType>
Array<myType>::Array(const Array<myType>& y){
  try
  {
    array = new myType[y.getCapacity()];
  }
  catch (const exception & e)
  {
    cout << "new exception " <<  e.what() <<  endl;
  }

  if (array != NULL){
    
    // set Size and capacity
    Size = y.size();
    capacity = y.getCapacity();
  
    // copy elements in Array y
    for (int i = 0;i < Size;i++)
      array[i] = y[i];
  }
  
}

// Array(int length,myType* values)
template <class myType>
Array<myType>::Array(int length, myType* values){
  try
  {
    array = new myType[length];
  }
  catch (const exception &e)
  {
    cout << "new exception " << e.what() << endl;
  }
  
  if (values != NULL and array != NULL){

    // set Size and capacity
    Size = length;
    capacity = length;
    
    // copy elements in Array y
    for (int i = 0;i < Size;i++)
      array[i] = values[i];

  }
  
}

// destructor
template <class myType>
Array<myType>::~Array(){
  cleanup();
}

// Initialize an array with size = s and assign all elements as v
template <class myType>
Array<myType>::Array(int s,myType v){
  
  // allocate memeory for the array
  try
  {
    array = new myType[s];
  }
  catch (const exception &e)
  {
    cout << "new exception " <<  e.what() << endl;
  }
  
  if (array != NULL){
    
    // set size and capacity
    Size = s;
    capacity = s;
    
    // initialize all elements as v
    for (int i = 0;i < Size;i++)
      array[i] = v;
  }
  
}

// get size
template <class myType>
int Array<myType>::size() const{
  return Size;
}

// append x to the end of the array
template <class myType>
void Array<myType>::append(myType x){
  
 // if the array is full, expand the capacity
  if (capacity){
     if (capacity == Size)
        this->expand();
   
    // append x to the end and update count
    array[Size++] = x;
  }
  
}

// append array y to the end of the array
template <class myType>
void Array<myType>::append(const Array<myType>& y){

 if (capacity){
    // copy all elements in y 
    for (int i = 0;i < y.size();i++){
      // When array is full, expand the capacity
      if (Size == capacity)
        this->expand();
    
      array[Size++] = y[i];
    }
  }
 
}

// overload of =
template <class myType>
Array<myType>& Array<myType>::operator=(const Array& y){
  if(this != &y){

    cleanup();
    try
    {
      array = new myType[y.getCapacity()];
    }
    catch(const exception &e)
    {
      cout << "new exception " << e.what() << endl;
    }
    
    if (array != NULL){
      
      // set size and capacity
      capacity = y.getCapacity();
      Size = y.size();
      
      for (int i = 0;i < Size;i++)
        array[i] = y[i];
    }
  }
 
  return *this;
}

// overload of []
template <class myType>
myType& Array<myType>::operator[](int index)const{

  // if the index is illegal, exit with status 0
  
  if (index < 0 or index >= Size)
    throw myError;
  else
    return array[index];
}

// get count
template <class myType>
int Array<myType>::getCapacity()const{
  return capacity;
}

// double the arraysize when the array is full
template <class myType>
void Array<myType>::expand(){

  // allocate a array with double size
  myType *newArray = NULL;
  int newCapacity = 2 * capacity;
  try
  {
    newArray = new myType[newCapacity];
  }
  catch (const exception &e)
  {
    cout << "new exception " << e.what() << endl << endl;
  }

  if(newArray != NULL){

    // copy all elements
    for (int i = 0;i < Size;i++)
      newArray[i] = array[i];

    cleanup();
    array = newArray;
    capacity = newCapacity;
  }
  
}

// overload of +
template <class myType>
Array<myType>& Array<myType>::operator+(const Array<myType>& y){
  
  // copy all elements in y
  Array<myType> copy = y;
  
  for (int i = 0;i < copy.size();i++){

    // When array is full, expand the capacity
    if (capacity == Size){
        expand();
    }
    array[Size++] = copy[i];
  }

  copy.cleanup();
  return *this;
}

//printf function for Array (overload of <<)
template <class myType>
ostream& operator<<(ostream& os, const Array<myType>& y)  
{  
  os << "[";
  int i;
  for (i = 0;i < y.size() - 1;i++){
      os << y[i] << ", "; 
  }
  os << y[i] << "]";
  
  return os;
}

// cleanup: release all memory associated with the array
template <class myType>
void Array<myType>::cleanup(){
  if (array != NULL){
    delete [] array;
    array = NULL;
  }

}

#endif
