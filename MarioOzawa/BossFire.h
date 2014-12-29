#ifndef _BOSSFIRE_H_
#define _BOSSFIRE_H_

#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"7
#define VXFire 0.7f


#pragma once
class BossFire : public MyObject
{
protected:
	Sprite* _curSprite;
	//float _vx,_vy;
public:
	int timeUpdate;
	BossFire(float x, float y,bool turnLeft);
	virtual ~BossFire(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void CheckCollision(MyObject* obj);
};

#endif