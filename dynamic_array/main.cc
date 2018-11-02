#include <iostream>
#include <sstream>
#include <stdlib.h>

// Include our array class definition and implementation
#include "array.h"
#include "array.cc"
#include <string>

using namespace std;

void Test1()
{ // Just create a vector with default constructor and add
  // elements with push_back and push_front.  Then retrieve
  // with only the indexing operator.  Allows destructor to clean up
  cout << "Starting Test1" << endl;
  array<string> v;
  for (int i=0; i<50; i++)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Print out results
  cout << "Test1 results" << endl;
  
  for (size_t i = 0; i < v.length(); ++i)
    {
      cout << v[i] << endl;
    }
}

void Test2()
{ // Just create a vector with default constructor and add
  // elements with push_back and push_front.  Then retrieve
  // with only the back() function and pop_back.  Also
  // tests "empty"
  cout << "Starting Test2" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      string tmp(oss.str().c_str());
      v.push_back(string(oss.str().c_str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Print out results
  cout << "Test2 results" << endl;
  
  while (!v.empty())
    {
      string st = v.back();
      v.pop_back();
      cout << st << endl;
    }
}

void Test3()
{ // Just create a vector with default constructor and add
  // elements with push_back and push_front.  Then retrieve
  // with only the front() function and pop_front.  Also
  // tests "empty"
  cout << "Starting Test3" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str().c_str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Print out results
  cout << "Test3 results" << endl;
  
  while (!v.empty())
    {
      string st = v.front();
      v.pop_front();
      cout << st << endl;
    }
}

void Test4()
{ // Same as test1 except tests the copy constructor and clear
  cout << "Starting Test4" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str().c_str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Now make a copy of the vector
  array<string> v1(v);
  
  // Print out results
  cout << "Test4 results" << endl;
  for (size_t i = 0; i < v1.length(); ++i)
    {
      cout << v1[i] << endl;
    }
  // clear the vector and print again
  v.clear();
  cout << "Test4 results again, should be empty" << endl;
  for (size_t i = 0; i < v.length(); ++i)
    {
      cout << v[i] << endl;
    }
}

void Test5()
{// Create a vector the print out using iterators
  cout << "Starting Test5" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str().c_str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Print out results
  cout << "Test5 results" << endl;
  array_iterator<string> it = v.begin();
  while(it != v.end())
    {
      cout << *it++ << endl;
    }
}

void Test6()
{ // test indexing operator on left-hand-size of assignment
  cout << "Starting Test6" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str().c_str()));
    }
  // Now use indexing operator to access (and chnage) elements
  for (size_t i = 0; i < v.length(); ++i)
    {
      ostringstream oss;
      oss << "Hello from string replaced " << i;
      v[i] = string(oss.str().c_str());
    }
  // And print results
  cout << "Test6 results" << endl;
  for (size_t i = 0; i < v.length(); ++i)
    {
      cout << v[i] << endl;
    }
}

  
#ifdef GRAD_STUDENT
void Test7()
{ // Test insert and erase (grad students only)
  cout << "Starting Test7" << endl;
  array<string> v;
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v.push_back(string(oss.str().c_str()));
    }
  for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string front " << i;
      v.push_front(string(oss.str().c_str()));
    }
  // Now find the 25th element and insert a new string before
  array_iterator<string> it;
  array_iterator<string> it1 = v.end();;
  size_t i = 0;
  for (it = v.begin(); it != v.end(); ++it)
    {
      if (++i == 25) it1 = it; // it1 is an iterator to 25th element
    }
  v.Insert(string("Inserted element before 25th"), it1);

  // Now print out using iterators
  cout << "Test7 results" << endl;
  array_iterator<string> it2 = v.end();
  size_t i2 = 0;
  for (array_iterator<string> it = v.begin(); it != v.end(); ++it)
    {
      cout << *it << endl;
      if (++i2 == 10) it2 = it; // Iterator for 10th element
    }
  // erase 10th and print again
  v.erase(it2);
  cout << "Test7 results again, should be missing 10th element" << endl;
  for (array_iterator<string> it = v.begin(); it != v.end(); ++it)
    {
      cout << *it << endl;
    }
}

void Test8()
{ // Grad students only, test special constructor
  cout << "Starting Test8" << endl;
  array<string> v(50, string("Replicated Constructor"));
  // And print out
  cout << "Test8 results" << endl;
  for (size_t i = 0; i < v.length(); ++i)
    {
      cout << v[i] << endl;
    }
  // Also test reserve
  array<string> v1;
  v1.reserve(10);
    for (int i = 0; i < 50; ++i)
    {
      ostringstream oss;
      oss << "Hello from string back " << i;
      v1.push_back(string(oss.str().c_str()));
    }
    // No need t print out; the constructor counts will verify correctness
}
#endif
  

int main(int argc, char** argv)
{ // If second arg specified, it is the test number to run
  // if not specified, run all
  int testNum = -1;
  if (argc > 1) testNum = atol(argv[1]);
  //string::ClearCounts();
  if (testNum < 0 || testNum == 1) { Test1(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 2) { Test2(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 3) { Test3(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 4) { Test4(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 5) { Test5(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 6) { Test6(); }//string::PrintCounts();}
#ifdef GRAD_STUDENT
  if (testNum < 0 || testNum == 7) { Test7(); }//string::PrintCounts();}
  if (testNum < 0 || testNum == 8) { Test8(); }//string::PrintCounts();}
#endif
}
