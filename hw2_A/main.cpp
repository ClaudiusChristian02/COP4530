/*  
   main.cpp
   01/21/15
   Chris Lacher

   Driver program for PostMachine object
*/

#include <iostream>
#include "post.h"

void ClearBuffer(std::istream& is)
{
	char ch;
	do
	{
		is.get(ch);
	} while ((!is.eof()) && (ch != '\n'));
}

int main()
{
  PostMachine m;
  bool loaded = 0;
  char response ('x');
  do
  {
    do loaded = m.Load();
    while (!loaded);
    m.Run();
    std::cout << "\n** Load another program? ";
    std::cin >> response;
	ClearBuffer(std::cin);
  }
  while (response == 'y' || response == 'Y');
  return EXIT_SUCCESS;
}
