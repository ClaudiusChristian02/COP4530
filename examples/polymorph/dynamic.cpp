/*   dynamic.cpp

     demonstration of polymorphic programming

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
#include <classes.cpp>

int main()
{
  B * bptr;
  int n;
  do
    {
      std::cout << "Enter type number (-1 to quit): ";
      std::cin >> n;
      if (std::cin.fail() || n < 0) break;
      switch(n)
	{
	case 0:
	  bptr = new B;
	  break;
	case 1:
	  bptr = new D1;
	  break;
	case 2:
	  bptr = new D2;
	  break;
	case 3:
	  bptr = new D3;
	  break;
	case 4:
	  bptr = new D4;
	  break;
	case 5:
	  bptr = new D5;
	  break;
	default:
	  return EXIT_SUCCESS;
	}
      bptr -> F();
      bptr -> G();
      bptr -> H();
      if (n == 5)
	{
	  dynamic_cast<D5*>(bptr)->F2();
	  dynamic_cast<D5*>(bptr)->G2();
	  dynamic_cast<D5*>(bptr)->H2();
	}
      delete bptr;
    }
  while (1);
  return EXIT_SUCCESS;
}
