/*   classes.cpp

     demonstraton class hierarchy

     is_a table:

             B    D1   D2   D3   B2
            --    --   --   --   --
       D1 |  x
       D2 |  x
       D3 |        x
       D4 |            x
       D5 |                  x    x


     B  <-- D1 <-- D3 <-- D5
     B  <-- D2 <-- D4
     B2 <-- D5 
*/

#include <iostream>
#include <stdlib.h>

class B
{
public:
  B()               { std::cout << "B()\n"; }
  virtual ~B()      { std::cout << "~B()\n"; }
  void F()          { std::cout << "B::F()\n"; }
  void G()          { std::cout << "B::G()\n"; }
  virtual void H()  { std::cout << "B::H()\n"; }
};

class D1 : public B
{
public:
  D1()  : B()       { std::cout << "D1()\n"; }
  virtual ~D1()     { std::cout << "~D1()\n"; }
  void G()          { std::cout << "D1::G()\n"; }
  void H()          { std::cout << "D1::H()\n"; }
};


class D2 : public B
{
public:
  D2()  : B()       { std::cout << "D2()\n"; }
  virtual ~D2()     { std::cout << "~D2()\n"; }
  void G()          { std::cout << "D2::G()\n"; }
  void H()          { std::cout << "D2::H()\n"; }
};

class D3 : public D1
{
public:
  D3()  : D1()      { std::cout << "D3()\n"; }
  virtual ~D3()     { std::cout << "~D3()\n"; }
  void G()          { std::cout << "D3::G()\n"; }
  void H()          { std::cout << "D3::H()\n"; }
};

class D4 : public D2
{
public:
  D4()  : D2()      { std::cout << "D4()\n"; }
  virtual ~D4()     { std::cout << "~D4()\n"; }
  void G()          { std::cout << "D4::G()\n"; }
  void H()          { std::cout << "D4::H()\n"; }
};

class B2
{
public:
  B2()               { std::cout << "B2()\n"; }
  virtual ~B2()      { std::cout << "~B2()\n"; }
  void F2()          { std::cout << "B2::F2()\n"; }
  void G2()          { std::cout << "B2::G2()\n"; }
  virtual void H2()  { std::cout << "B2::H2()\n"; }
};

class D5 : public D3, public B2
{
public:
  D5()  : D3(), B2() { std::cout << "D5()\n"; }
  virtual ~D5()      { std::cout << "~D5()\n"; }
  void G()           { B2::G2(); std::cout << "D5::G()\n"; }
  void H()           { B2::H2(); std::cout << "D5::H()\n"; }
  void G2()          { std::cout << "D5::G2()\n"; }
  void H2()          { std::cout << "D5::H2()\n"; }
};

