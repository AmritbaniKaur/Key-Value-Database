#pragma once
/////////////////////////////////////////////////////////////////////
// CppProperties.h - Defines read/write and read only properties   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
//
// Got the idea from discussion here (scroll down about halfway):
// http://stackoverflow.com/questions/8368512/does-c11-have-c-style-properties
// This implementation is quite different however.
/*
 * - fixed bug in Property class by adding copy constructor that only
 *   copies data member value.  The default copy constructor copies
 *   all memebers including getter_ and setter_
*/
#include <iostream>
#include <functional>

/////////////////////////////////////////////////////////////////////
// Property<T> class provides encapsulated properties for C++
// - getter and setter functions can be customized without changing
//   the client interface for any class that uses Property<T>
//
template<typename T>
class Property
{
public:
  // initialize the property field

  Property() : value(T()) {}
  Property(const Property<T>& p) : value(p.value) {}  // added this fix
  Property(const T& t) : value(t) {}
  virtual ~Property() {}
  
  // set the property field with assignment operator

  virtual Property<T>& operator=(const T &t)
  { 
    value = setter_(t); 
    //getter_ = [=]() { return value; }  // Ronak's solution
    return *this; 
  }
  // get the property field with cast operator

  virtual operator const T() const { return getter_(); }
  
  // define methods to customize getter and setter behaviors

  void setter(std::function<T(const T&)> sttr) { setter_ = sttr; }
  void getter(std::function<T(void)> gttr) { getter_ = gttr; }
  T getValue() { return value; }  // used by custom getters

protected:
  T value;  // property field

  // define default getter and setter behavior using lambdas

  std::function<T(const T&)> setter_ = [](const T& t) { return t; };  // setter
  std::function<T()> getter_ = [=]() { return value; };               // getter
};

/*----< overload insertion operator for std::string properties >---*/

std::ostream& operator<<(std::ostream& out, Property<std::string>& p)
{
  std::string temp = p;
  try {
    out << (temp).c_str();
  }
  catch (std::exception& ex)
  {
    std::cout << "\n  exception:\n  " << ex.what() << "\n";
  }
  return out;
}

/////////////////////////////////////////////////////////////////////
// Property<const T> class provides encapsulated properties for C++
// - getter function can be customized without changing
//   the client interface for any class that uses Property<T>
// - no setter is provided since the class is used for const properties
// - comments for this class would be same as above, and so are omitted
//
template<typename T>
class Property<const T>
{
public:
  Property() : value(T()) {}
  Property(const Property<T>& p) : value(p.value) {}
  Property(const T& t) : value(t) {}
  virtual ~Property() {}
  void getter(std::function<T(void)> gttr) { getter_ = gttr; }
  virtual operator const T() const { return getter_(); }    // getter
  T getValue() { return value; }                            // used by custom getters
protected:
  T value;
  std::function<T()> getter_ = [=]() { return value; };     // default gettter
};

/*----< overload insertion operator for std::string properties >---*/

std::ostream& operator<<(std::ostream& out, Property<const std::string>& p)
{
  std::string temp = p;
  try {
    out << (temp).c_str();
  }
  catch (std::exception& ex)
  {
    std::cout << "\n  exception:\n  " << ex.what() << "\n";
  }
  return out;
}

