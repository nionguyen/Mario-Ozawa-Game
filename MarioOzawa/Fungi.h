#ifndef _FUNGI_H_
#define _FUNGI_H_

#define GRAVITY		0.01
#define BOTTOM		600

#include "Sprite.h"
#include "MyObject.h"

#pragma once
class fungi : public MyObject
{
protected:
	Sprite* _curSprite;
	//0: Left | 1: Right
	//bool _turnLeft;

	//float _vx;
	//float _vy;
	int _timeTransform;
public:
	fungi(float x, float y,State state);
	virtual ~fungi(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	CRECT GetReSizeRect();
	void CheckCollision(MyObject* obj);

	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif