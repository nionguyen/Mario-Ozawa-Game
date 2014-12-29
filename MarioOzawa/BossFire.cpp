#include "BossFire.h"
#include "ResourceManager.h"
#include "TileMap.h"
BossFire::BossFire(float x, float y,bool turnLeft) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/FireBoss.png"), 100);
	//_curSprite->_start = 0;
	//_curSprite->_end = 3;
	_vx = 0;
	_turnLeft = turnLeft;
	_State = Move;
	_vy = 0;
	timeUpdate = 0;
	_ID = EObject::BOSSFIRE;
}


BossFire::~BossFire(void)
{
	delete _curSprite;
}

void BossFire::Update(int time)
{
	if(_State == dead)
		return;

	_x += _vx*time;
	if(_turnLeft == true)
		_vx = -VXFire ;
	else _vx = VXFire;
	
	_curSprite->Update(time);

	timeUpdate+= time;

	if(timeUpdate >= 1800)
		_State = dead;
}

void BossFire::Render()
{
	if(_State == dead)
		return;
	if(_turnLeft == false)
		_curSprite->Render(_x,_y);
	else _curSprite->RenderScaleX(_x,_y);
}

void BossFire::CheckCollision(MyObject* obj)
{
	if((_State == dead) || (_State == beforedead))
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect())!= None )
		{
			obj->_State = transform;
			if(GL_CurForm != 0)
				GL_NextForm = GL_CurForm - 1;
			if(GL_CurForm == 0)
			{
				obj->_vy = -2.0;
				obj->_State = beforedead;
				return;
			}
		}
	}
}

CRECT BossFire::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height );
}

