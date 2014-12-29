#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"
#include "Bullet.h"
#include "BrickItem.h"

#include <vector>
#define MARIO_VX	0.5f	//velocity of mario
#define MARIO_VY	2.2f
#define MAX_MARIO_VX 0.65f	//max velocity of mario
#define MAX_MARIO_VY 2.0f
#define GRAVITY		0.01f	//gravity ratio
#define FRICTION_X	0.002f //0.0000006f //friction of mario
#define ACCEL_X		1.5f //1.5 //accelerator of mario
#define BOTTOM		600
#define DISTANCE_WITH_LAST_POSITION_X 400 //distance between the current position and last position to update last position
#define FALL_DEAD_HIGH 4	//the high mario fall out of game before reborn
#define DELTA_RECT_X 0 //delta to sub in x when call getRect
#define DELTA_RECT_Y 0 //delta to sub in y when call getRect

#define EXP_FOR_BRICK 5 //point for exp
#define EXP_FOR_OBJECT 10
#define TIME_REBORN 1500 //thoi gian sau khi mario reborn hien thi o che do blur, truoc khi reborn hoan chinh

#define MARIO_VX_COMPLETE_MAP 0.50f
#define MARIO_DELTA_X_COMPLETE_MAP 400

#define MARIO_FIRE_TIME 250 //thoi gian giua 2 lan ban

using namespace std;

#pragma once

//Player ~ main character
class Mario : public MyObject
{
protected:
	
	int _TimeTransform;
	int _time;
	int _TimeFire;
	int _startx; //the last position at that mario is (move or stand) and alive
	int _starty;

	vector <bullet*> _listBullet;

public:
	Sprite* _sprMarioSmaller;
	Sprite* _sprMarioLarger;
	Sprite* _sprMarioFire;
	Sprite* _curSprite;

	int gold;
	int life; //số mạng sống còn lại của mario
	int exp;

	Mario(float x, float y);
	virtual ~Mario(void);

	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	CRECT GetRect1();
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stand();

	//tan long
	void ShitDown();

	//call when you want mario die
	void RunBeforeDie();

	//fire bullets
	void Fire();

	//call 1 time to transform
	void TransformMario(int curForm,int nextForm);

	//effect transform mario from: small->big->fire
	void Transform();

	//override
	virtual void CheckCollision(MyObject* obj);
	virtual void CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height);
	virtual void UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision);
};

#endif
