
#ifndef _TURTLE_H_
#define _TURTLE_H_

#define GRAVITY		0.01
#define BOTTOM		600

#include "Sprite.h"
#include "MyObject.h"

#pragma once
class turtle : public MyObject
{
public:
	Sprite* _curSprite;
	//0: Left | 1: Right
	//bool _turnLeft;

	//float _vx;
	//float _vy;
	int _TimeStand;
	int _TimeAttack;
public:
	turtle(float x, float y,State state);
	virtual ~turtle(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
	// change bound box other size
	CRECT GetReSizeRect1();
	CRECT GetReSizeRect2();
	CRECT GetReSizeRect3();
	void CheckCollision(MyObject* obj);
};

#endif
