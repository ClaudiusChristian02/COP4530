/*
    finteger.cpp
    11/12/13
    Chris Lacher

    functionality test of the Integer class
*/

#include <iostream>
#include <integer.cpp>

int main()
{
  
  fsu::Integer a, b;
  char op;
  std::cout << "This is a test of fsu::Integer arithmetic\n";
  while (1)
  {
    std::cout << "Enter [arg] [op] [arg]: ";
    std::cin >> a >> op;
    switch(op)
    {
      case '+':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            a += b;
            std::cout << op << ' ' << b << " : a == " << a;
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a + b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '-':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            a -= b;
            std::cout << op << ' ' << b << " : a == " << a;
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a - b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '*':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            a *= b;
            std::cout << op << ' ' << b << " : a == " << a;
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a * b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '/':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            a /= b;
            std::cout << op << ' ' << b << " : a == " << a;
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a / b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '%':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            a %= b;
            std::cout << op << ' ' << b << " : a == " << a;
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a % b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '=':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            std::cout << op << ' ' << b << " == "
                      << (a == b);
            break;
          case ' ':
            std::cin >> b;
            a = b;
            std::cout << ' ' << b << ": a == " << a;
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '!':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            std::cout << op << ' ' << b << " == "
                      << (a != b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '<':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            std::cout << op << ' ' << b << " == "
                      << (a <= b);
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a < b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      case '>':
        std::cout << "  "  << a << ' ' << op;
        std::cin.get(op);
        switch(op)
        {
          case '=':
            std::cin >> b;
            std::cout << op << ' ' << b << " == "
                      << (a >= b);
            break;
          case ' ':
            std::cin >> b;
            std::cout << ' ' << b << " == "
                      << (a > b);
            break;
          default:
            do std::cin.get(op); while (op != '\n' && !std::cin.eof());
            std::cout << " bad operator: try again";
            break;
        }
        break;

      default:
        do std::cin.get(op); while (op != '\n' && !std::cin.eof());
        std::cout << "bad operator: try again";
    }
    std::cout << '\n';
  }
  return 0;
}
