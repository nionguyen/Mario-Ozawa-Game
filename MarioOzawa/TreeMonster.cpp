#include "TreeMonster.h"
#include "ResourceManager.h"
#include "TileMap.h"

TreeMonster::TreeMonster(float x, float y) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/TreeMonster.png"), 100);
	_x = x;
	_y = y;
	_oriX = x;
	_oriY = y;
	_vx = 0;
	_vy = 0;
	_ID = EObject::TREEMONSTER;
	_State = stand;
	_timeStand = 100;
	_timeStandUp = 0;
}


TreeMonster::~TreeMonster(void)
{
	delete _curSprite;
}

void TreeMonster::Update(int time)
{
	if(_State == dead)
		return;
	if(_State == stand)
	{
		_timeStand++;
		if(_timeStand >= 150)
		{
			_timeStand = 0;
			_State = moveUp;
			_vy = -0.13;
		}
		return;
	}
	if(_State == moveUp)
	{
		if( (_oriY - _y) < 50 )
			_y += _vy * time;
		else
		{
			_timeStandUp++;
			if(_timeStandUp >= 150)
			{
				_timeStandUp = 0;
				_State = moveDown;
				_vy = 0.13;
			}
		}
	}

	if(_State == moveDown)
	{
		if(_y < _oriY)
			_y += _vy * time;
		else
		{
			_State = stand;
			_curSprite->_index = 0;
		}
	}

	_curSprite->Update(time);
}

void TreeMonster::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x,(int)_y);
}

void TreeMonster::CheckCollision(MyObject* obj)
{
	return;
	if((_State == stand) || (_State == dead))
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == transform) || (obj->_State == dead) || (obj->_State == beforedead))
			return;
		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != EDirect::None)
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

CRECT TreeMonster::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height);
}
