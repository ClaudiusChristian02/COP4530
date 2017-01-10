/*
    debug.h
    01/01/09
    Chris Lacher

    Definition of the class Debug

    The Debug class is handy in tracing program flow.
    Use Debug objects by inserting one line 

      Debug d("method name");

    at the beginning of the scope. The effect is to signal the
    entrance and exit of each call.  In fact, it is instructive to
    use this facility in general, just to see how function calls
    work.  A picture of the runtime stack is written to screen.  
    The technique is illustrated in xstring.* (commented out).

    Revised to new style standard in 2005

    Copyright 2009, R.C. Lacher
*/

#ifndef _DEBUG_H
#define _DEBUG_H

#include <iostream>
#include <string.h>

namespace fsu
{

  class Debug
  {
  public:
    Debug(const char* name)
    // normally a 1-parameter constructor is not a good idea
    { 
      scopeName_ = new char [1 + strlen(name)];
      strcpy(scopeName_,name);
      std::cout << "Debug: " << scopeName_ << " entered\n" << std::flush;
    }

    ~Debug()
    {
      std::cout << "Debug: " << scopeName_ << " exited\n" << std::flush;
      delete [] scopeName_;
    }

  private:
    char* scopeName_;
  } ; // class debug

}   // namespace fsu
#endif
