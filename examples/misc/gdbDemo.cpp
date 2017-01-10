/* 
  gdbDemo.cpp

  a defective attempt at recursive caculation of factorial,
  and a short tutorial on using the gnu dynamic debugger gdb

  Tutorial Instructions:

  1. Compile with the command "g++ -odemo.x -Wall -Wextra gdbDemo.cpp".

     The program should compile without errors or warnings and produce the
     executable named "demo.x".

  2. Enter "demo.x" and note the program behavior. You should get a runtime
     error and a "core dump" file.

  3. Compile again with the command "g++ -g -odemo.x gdbDemo.cpp" and run "gdb
     demo.x" from the command line. Then type "run" at the gdb prompt. The
     program stops in recursion. At what line?

  4. Find information about the "gdb" utility. What is it used for? Why was it
     necessary to compile your program with option "-g"?

  5. Compile this program with "g++ -g -odemo.x gdbDemo.cpp" and run "gdb
     demo.x" from the command line. Then enter "break fact" at the gdb prompt,
     followed by "run" and several "step" (stop the run by the command "quit"):

     g++ -g -odemo.x gdbDemo.cpp
     gdb demo.x
     break fact
     run
     step
     step
     step
     step
     quit

     What do you notice about the values of "k" passed to "fact"?

  6. Repeat step 5, and while the gdb is running enter the command "bt" (for
     backtrace):

     g++ -g -odemo.x gdbDemo.cpp
     gdb demo.x
     break fact
     run
     step
     step
     step
     step
     bt

     Note that bt shows the current state of the runtime function call stack.

  6. You should now have some info about what to fix in the program.

  7. Look at the various places where integer types are specified, and come up
     with a better plan for these types.

*/

#include <iostream>

int fact(int k)
{
  if (k = 0) return 1;
  else return k*fact(k-1);
}

int main()
// calculates 5!
{
  int n = 5;
  std::cout << n << "! = " << fact(n) << '\n';
}
