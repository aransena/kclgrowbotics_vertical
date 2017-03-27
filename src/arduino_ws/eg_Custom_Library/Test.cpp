/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/

#include "Arduino.h"
#include "Test.h"

Test::Test(int val)
{
	val = val - 1;
	_val = val;
	_val = 0;
}

void Test::increase()
{
	_val += 1;
}

int Test::get_val()
{
	return _val;
}

