/////////////////////////////////////////////////////////////////////
// CppProperties.cpp - Defines read/write and read only properties //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_CPPPROPERTIES

#include "CppProperties.h"
#include <string>
#include <iostream>

class X
{
public:
  Property<std::string> name;
  Property<double> isMutable;
  Property<const double> pi = 3.1415927;
  Property<const std::string> constName = "a const name";
};

/////////////////////////////////////////////////////////////////////
// Z class:
// - demonstrates how to customize getter and setter functions
//   without changing public interface of Z.
// - That is important because it means that should we decide,
//   after a class was published, that we should control the
//   way the property behaves, we won't break existing clients.

/*----< demo function for custom getter and setter >---------------*/

std::string toUpper(const std::string& str)
{
  std::string upperS = str;
  for (auto& c : upperS)
    c = toupper(c);
  return upperS;
}

class Z
{
public:
  Z()
  {
    // return value of setter is assigned to Property value
    name.setter(
      [](const std::string& s) { return toUpper(s); }  // set all chars to upper case
    );
    // this also works:
    // name.setter(toUpper);

    // return value of getter is returned from cast to Property type
    name.getter(
      [=]() { 
        std::string s = name.getValue(); 
        s[0] = tolower(s[0]);               // set first char to lower case
        return s; 
      }
    );
  }
  Property<std::string> name;
};

/////////////////////////////////////////////////////////////////////
// - We can also modify the behavior of the propert by overriding
//   the property virtual functions.  That, however, modifies user
//   interface.
//
class UpperCaseProperty : public Property<std::string>
{
public:
  UpperCaseProperty(const std::string& s) 
  { 
    value = toUpper(s); 
  }
  virtual Property<std::string>& operator=(const std::string &s)
  {
    value = toUpper(s);
    return *this;
  }
};

class Y
{
public:
  UpperCaseProperty name = "jim";
};

int main()
{
  std::cout << "\n  Demonstrate C++ Properties class";
  std::cout << "\n ==================================";

  X x;
  x.name = "Jim";
  std::cout << "\n  x.name = " << x.name;
  std::cout << "\n  x.pi = " << x.pi;
  std::cout << "\n  x.isMutable = " << x.isMutable;
  x.isMutable = x.pi;
  std::cout << "\n  x.isMutable = " << x.isMutable;
  std::cout << "\n  x.constName = " << x.constName;

  std::cout << "\n  making a copy of x, called newX:";
  std::cout << "\n ----------------------------------";
  X newX(x);
  newX.name = "joe";
  std::cout << "\n  newX.name = " << newX.name;

  //x.constName = "a new name";  // fails to compile - that's good

  std::cout << "\n";
  std::cout << "\n  demonstrate overriding property \"getter\" function";
  std::cout << "\n ---------------------------------------------------";
  Y y;
  std::cout << "\n  y.name = " << y.name;

  std::cout << "\n";
  std::cout << "\n  demonstrate providing custom getter and setter functions";
  std::cout << "\n ----------------------------------------------------------";
  Z z;
  z.name = "fawcett";
  std::cout << "\n  z.name = " << z.name;
  std::cout << "\n\n";
}
#endif
