#ifndef _BRICKQUESTION_H_
#define _BRICKQUESTION_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"



#pragma once
class brickQuestion : public MyObject
{
protected:
	Sprite* _curSprite;
	Sprite* _coin;
	bool _drawCoin;
	int _xCoint,
		_yCoint;
public:
	brickQuestion(float x, float y,State state);
	virtual ~brickQuestion(void);
	virtual void Update(int time);
	virtual void Render();
	void CheckCollision(MyObject* obj);
	//virtual CRECT GetRect();
};

#endif

