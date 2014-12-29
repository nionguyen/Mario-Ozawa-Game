#ifndef _BULLET_H_
#define _BULLET_H_

#define GRAVITY		0.01

#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"



#pragma once
class bullet : public MyObject
{
protected:
	Sprite* _curSprite;
	//float _vx,_vy;
public:
	bullet(float x, float y,bool turnLeft);
	virtual ~bullet(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
	void CheckCollision(MyObject* obj);
};

#endif