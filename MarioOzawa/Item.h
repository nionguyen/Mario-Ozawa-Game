#ifndef _ITEM_H_
#define _ITEM_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"
#define GRAVITY		0.01
enum EBrickItemKind
{
	FLOWER, 
	LARGER, 
	SHOOTER 
};
#pragma once

//class perform normal brick
// + can not break
// + just check collision + Render
class Item : public MyObject
{
protected:


	float oriY;
public:
	EBrickItemKind _item;
	Sprite* _curSprite;
	Item(float x, float y, EBrickItemKind kindOfItem);
	virtual ~Item(void);
	virtual void Update(int time);
	virtual void Render();
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual CRECT GetRect();
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
	void CheckCollision(MyObject* obj);
};

#endif