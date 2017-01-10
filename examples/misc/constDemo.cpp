/* paramdemo.cpp
   09/30/06

   demonstrates various ways of passing parameters

*/

#include <iostream>

class D
{
public:
  enum State
  {
    initial, modified
  };

  D() : state(initial) {}

  State state;
};

std::ostream& operator << (std::ostream& os, D d)
{
  switch (d.state)
    {
    case D::initial:
      os << "initial";
      break;
    case D::modified:
      os << "modified";
      break;
    }
  return os;
}

void ValDemo (D d)
{
  d.state = D::modified;
  std::cout << "    ValDemo state of local variable is: " << d << '\n';
} 

void RefDemo (D& d)
{
  d.state = D::modified;
  std::cout << "    RefDemo state of local variable is: " << d << '\n';
} 

void PtrDemo (D* p)
{
  p -> state = D::modified;
  std::cout << "    PtrDemo state of local variable is: " << *p << '\n';
} 

int main()
{
  D d;
  D* p = new D;

  std::cout << "Calling ValDemo(d)   pre-call state is: " << d << '\n';
  ValDemo(d);
  std::cout << "                    post-call state is: " << d << "\n\n";

  d.state = D::initial;
  std::cout << "Calling RefDemo(d)   pre-call state is: " << d << '\n';
  RefDemo(d);
  std::cout << "                    post-call state is: " << d << "\n\n";

  std::cout << "Calling PtrDemo(d)   pre-call state is: " << *p << '\n';
  PtrDemo(p);
  std::cout << "                    post-call state is: " << d << "\n\n";

};
