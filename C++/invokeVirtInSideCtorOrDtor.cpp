/*
 * check what happens when invoking virtual method inside C-tor and D-tor.
 *
 * gcc compile command is :
 * g++ -Wall invokeVirtInSideCtorOrDtor.cpp -o invokeVirtInSideCtorOrDtor
 *
 */

#include <iostream>
#include <string>

void println(std::string const& msg)
{ std::cout << msg << '\n'; }

class Base
{
 public:
  Base()              { println("Base::Base()");  virt(); }
  virtual void virt() { println("Base::virt()"); }
  virtual ~Base()     { println("Base::~Base()"); }
};

class Derived : public Base
{
 public:
  Derived()           { println("Derived::Derived()");  virt(); }
  virtual void virt() { println("Derived::virt()"); }
  virtual ~Derived()  { println("Derived::~Derived()"); }
};

int main()
{
  Derived d;
}

// Output:

// Base::Base()
// Base::virt()        // ← Not Derived::virt()
// Derived::Derived()
// Derived::virt()
// Derived::~Derived()
// Base::~Base()       // ← Not Derived::~Derived()
