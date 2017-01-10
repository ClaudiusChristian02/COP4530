/*   static.cpp

     demonstration of inheritance characteristics for compile-time bindings

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
  std::cout << "Declaring b:\n";
  B b;
  std::cout << "Declaring d1:\n";
  D1 d1;
  std::cout << "Declaring d2:\n";
  D2 d2;
  std::cout << "Declaring d3:\n";
  D3 d3;
  std::cout << "Declaring d4:\n";
  D4 d4;
  std::cout << "Declaring d5:\n";
  D5 d5;

  int n;
  do
    {
      std::cout << "Enter type number (-1 to quit): ";
      std::cin >> n;
      if (std::cin.fail() || n < 0) break;
      switch(n)
	{
	case 0:
          b.F();
	  b.G();
	  b.H();
	  break;
	case 1:
          d1.F();
	  d1.G();
	  d1.H();
	  break;
	case 2:
          d2.F();
	  d2.G();
	  d2.H();
	  break;
	case 3:
          d3.F();
	  d3.G();
	  d3.H();
	  break;
	case 4:
          d4.F();
	  d4.G();
	  d4.H();
	  break;
	case 5:
          d5.F();
	  d5.G();
	  d5.H();
          d5.F2();
	  d5.G2();
	  d5.H2();
	  break;
	default:
	  return EXIT_SUCCESS;
	} // switch
    } // do
  while (1);
  std::cout << "Variables going out of scope:\n";
  return EXIT_SUCCESS;
}
