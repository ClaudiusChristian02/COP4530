/*  
   main.cpp
   01/21/15
   Chris Lacher

   Driver program for PostMachine object
*/

#include <iostream>
#include <post.h>

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
  }
  while (response == 'y' || response == 'Y');
  return EXIT_SUCCESS;
}
