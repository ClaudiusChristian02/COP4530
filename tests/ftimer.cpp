/*  ftimer.cpp
    Sep 26 1998
    Chris Lacher

    functionality test of timer utilities
    9/26/98

    Copyright 1998 - 2007, R. C. Lacher
*/

#include <timer.cpp>

int main()
{
  const fsu::Instant z(0,0);
  fsu::Instant i,j;
  std::cout << "Instant::Write test\n";
  std::cout << "Enter Instant (secs:usecs) : ";
  std::cin >> i;
  do
  {
    std::cout << "           Instant as read: " << i.sec_ << ':' << i.usec_ << '\n';
    std::cout << "                     msecs: ";
    i.Write_mseconds(std::cout,2);
    std::cout << '\n';
    std::cout << "                      secs: ";
    i.Write_seconds(std::cout,2);
    std::cout << '\n';
    std::cout << "                      mins: ";
    i.Write_minutes(std::cout,2);
    std::cout << '\n';
    std::cout << "                       hrs: ";
    i.Write_hours(std::cout,2);
    std::cout << '\n';
    std::cout << "                      time: ";
    i.Write_time(std::cout,2);
    std::cout << '\n';
    std::cout << "Enter Instant (0:0 to exit): ";
    std::cin >> i;
  }
  while (i != z);

  std::cout << "Instant::arithmetic test\n";
  std::cout << "Enter [Instant][op][Instant] ('x' to exit): ";
  char op;
  while (std::cin >> i >> op >> j)
  {
    std::cout << "\n  ";
    std::cout << i << ' ' << op << ' ' << j << " == ";
    switch(op)
    {
      case '+':
        std::cout << i + j;
        break;
      case '-':
        std::cout << i - j;
        break;
      default:
        std::cout << "** bad op entered -- cannot compute result";
    }
    std::cout << "\n\nEnter [Instant][op][Instant] ('x' to exit): ";
  }
  std::cout << "End of test\n";
  return 0;
}
