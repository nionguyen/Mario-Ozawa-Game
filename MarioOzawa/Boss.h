#ifndef _FUNGI_H_
#define _FUNGI_H_

#define GRAVITY		0.01
#define BOTTOM		600
#define VX 0.1f
#include <vector>
#include "Sprite.h"
#include "MyObject.h"
#include "BossFire.h"
using namespace std;
#pragma once
class Boss : public MyObject
{
protected:
	//0: Left | 1: Right
	bool _turnLeft;

	int MinX,MaxX;
	int timehurt;
	
public:
	Sprite* _curSprite;
	int Hp;
	vector <BossFire*> _listFire;
	Boss(float x, float y,int _MinX,int _MaxX);
	virtual ~Boss(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	//CRECT GetReSizeRect();
	void CheckCollision(MyObject* obj);
	//virtual void CheckTitleCollision(float &_vx,float &_vy,float _nextX,float _nextY,float _maxWidth,float _maxHeight,int _width,int _height);

};

#endif