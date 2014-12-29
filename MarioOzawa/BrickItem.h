#ifndef _BRICKITEM_H_
#define _BRICKITEM_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"
#include "Item.h"

#pragma once

//perform brick have item hide on
// + can not break
// + collision
// + have item in it



class brickItem : public MyObject
{
public:
	Sprite* _curSprite;
	Item* _item;
public:
	EBrickItemKind _kindofitem;

	//kindOfItem = 0:hoa | 1:nam do | 2:namxanh 
	brickItem(float x, float y, EBrickItemKind kindOfItem,State state);
	virtual ~brickItem(void);
	virtual void Update(int time);
	virtual void Render();
	virtual void CheckCollision(MyObject* obj);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif

