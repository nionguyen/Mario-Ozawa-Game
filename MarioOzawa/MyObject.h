#pragma once

#include "Rect.h"
#include "ListCollisionData.h"

using namespace std;

//super class for all object in game
class MyObject
{
public:
	State _State;
	
	// tieu nun
	float _x;
	float _y;

	//next position
	float _nextx;
	float _nexty;
	
	//velocity
	float _vx;
	float _vy;
	
	//id to regonize what it is
	EObject _ID;
	
	//check if it is turn left or turn right
	//0: Left | 1: Right
	bool _turnLeft;
	//end tieu nun

	ListCollisionData _listCollisionData;

	MyObject(float x, float y);
	//MyObject(const MyObject* obj);
	virtual ~MyObject(void);

	virtual CRECT GetRect();

	//obj can check collision with other or not
	virtual bool CanCollide();

	//obj is alive, can update and render
	virtual bool IsAlive();

	virtual void Update(int time);

	virtual void Render();

	//check collision with another obj
	virtual void CheckCollision(MyObject* obj);

	// tieu nun
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);

	EDirect GetCollisionDirection(CRECT r1, CRECT r2);

	void RealTimeCollision(CRECT r1, CRECT r2);
	virtual void RealTimeCollision1(CRECT r1, MyObject *obj,int indexObject,int time);
	virtual float GetDistance(float x0,float y0,float x1,float y1);

	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

