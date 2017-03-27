/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/

#ifndef Test_h
#define Test_h

#include "Arduino.h"

class Test
{
  public:
    Test(int val);
    void increase();
    int get_val();
	
	private:
		int _val;
};
#endif
