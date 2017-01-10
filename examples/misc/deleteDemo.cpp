
#include <iostream>

const size_t arraySize = 10;

class Demo
{
public:
  Demo()
  {
    ++constructorCalls_;
    std::cout << "Demo() called " << constructorCalls_ << " times\n";
  }
  ~Demo()
  {
    ++destructorCalls_;
    std::cout << "~Demo() called " << destructorCalls_ << " times\n";
  }
  static int constructorCalls_, destructorCalls_;
};

int Demo::constructorCalls_ = 0;
int Demo::destructorCalls_ = 0;

void f1()
{
  std::cout << "bracket delete:\n";
  Demo * demoArray = new Demo [arraySize];
  delete [] demoArray;
  std::cout << "constructor/destructor deficit = " << Demo::constructorCalls_ - Demo::destructorCalls_ << '\n';
}

void f2()
{
  std::cout << "non-bracket delete:\n";
  Demo * demoArray = new Demo [arraySize];
  delete demoArray;
  std::cout << "constructor/destructor deficit = " << Demo::constructorCalls_ - Demo::destructorCalls_ << '\n';
}

void f3() // runtime error, core dump
{
  std::cout << "bracket delete after increment:\n";
  Demo * demoArray = new Demo [arraySize];
  ++demoArray;
  delete [] demoArray;
  std::cout << "constructor/destructor deficit = " << Demo::constructorCalls_ - Demo::destructorCalls_ << '\n';
}

int main()
{
  f1();
  f2();
  //  f3();
}
