#ifndef _COIN_H_
#define _COIN_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"



#pragma once
class coin : public MyObject
{
protected:
	Sprite* _curSprite;
public:
	coin(float x, float y,State state);
	virtual ~coin(void);
	virtual void Update(int time);
	virtual void Render();
	void CheckCollision(MyObject* obj);
	virtual CRECT GetRect();
};

#endif