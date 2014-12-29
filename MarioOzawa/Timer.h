
#include "Global.h"
#include <vector>
using namespace std;

//count millisecond
class MyTimer
{
public:
	~MyTimer();

	static void (*_handler)();

	static long _startTime;
	static long _totalTime;
	static long _currentTime;

	static void CreateNewTimer(long time, void (*handler)())
	{
		_startTime = GetTickCount();
		_totalTime = time;
		_handler = handler;
	}

	static void Update()
	{
		if(_totalTime <= 0)
			return;
		_currentTime = GetTickCount();
		if(_currentTime - _startTime >= _totalTime)
		{
			_currentTime = 0;
			_startTime = 0;
			_totalTime = 0;
			if(_handler)
			{
				_handler();
				_handler = NULL;
			}
		}
	}
};

long MyTimer::_startTime = 0;
long MyTimer::_currentTime = 0;
long MyTimer::_totalTime = 0;
void (*MyTimer::_handler)() = NULL;
