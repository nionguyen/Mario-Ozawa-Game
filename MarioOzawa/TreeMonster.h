#ifndef _TREEMONSTER_H_
#define _TREEMONSTER_H_

#include "Sprite.h"
#include "MyObject.h"

#pragma once
class TreeMonster : public MyObject
{
protected:
	Sprite* _curSprite;
	int _timeStand;
	int _timeStandUp;
	//toa. do x,y goc khi bat dau;
	float _oriX,_oriY;
public:
	TreeMonster(float x, float y);
	virtual ~TreeMonster(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void CheckCollision(MyObject* obj);
};

#endif
