#include "Boss.h"
#include "ResourceManager.h"
#include "TileMap.h"

Boss::Boss(float x, float y,int _MinX,int _MaxX) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Boss.png"), 100);
	_turnLeft = true;

	_x = x;
	//_y = y;
	_y = 390;
	MaxX = _MaxX;
	MinX = _MinX;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	if(_turnLeft == true)
		_vx = -VX;
	else _vx = VX;

	_State = Move;

	timehurt = 0;

	Hp = 5;

	_ID = EObject::BOSS;
}

Boss::~Boss(void)
{
	delete _curSprite;
}

void Boss::Update(int time)
{
	int size = _listFire.size();
	BossFire* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listFire[i];
		sf->Update(time);
	}

	if((_State == Move) || (_State == attack))
	{
		if(_State == Move)
			_curSprite->Update(time);
		if((_State == attack) && (_curSprite->_index != 3))
			_curSprite->Update(time);
	}


	if(_State == Move)
		_x += _vx * time;
	if(_State == Move)
	{
		if(_x <= MinX)
		{
			_x += 2;
			_turnLeft = false;

			_State = attack;
			_curSprite->_start = 0;
			_curSprite->_end = 3;

			BossFire* sf;
			if(_turnLeft == true)
				sf = new BossFire(_x - 30,_y + 35,_turnLeft);
			else sf = new BossFire(_x + 50,_y + 35,_turnLeft);
			_listFire.push_back(sf);
		}
		if(_x >= MaxX)
		{
			_x -= 2;
			_turnLeft = true;

			_State = attack;
			_curSprite->_start = 0;
			_curSprite->_end = 3;

			BossFire* sf;
			if(_turnLeft == true)
				sf = new BossFire(_x - 30,_y + 35,_turnLeft);
			else sf = new BossFire(_x + 50,_y + 35,_turnLeft);
			_listFire.push_back(sf);
		}
	}
	if(_State == attack)
	{
		if(_curSprite->_index == 3)
		{
			_curSprite->_start = 0;
			_curSprite->_end = 2;
			_State = Move;
		}
	}
	if(_turnLeft == true)
		_vx = -VX;
	else _vx = VX;
	if(_State == hurt)
	{
		timehurt+= 1*time;
		if(timehurt >= 400)
		{
			_State = attack;
			_curSprite->_start = 0;
			_curSprite->_end = 3;
			timehurt = 0;

			BossFire* sf;
			if(_turnLeft == true)
				sf = new BossFire(_x - 30,_y + 35,_turnLeft);
			else sf = new BossFire(_x + 50,_y + 35,_turnLeft);
			_listFire.push_back(sf);
		}
	}
	if(Hp == 0)
		_State = dead;
}

void Boss::Render()
{
	int size = _listFire.size();
	BossFire* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listFire[i];
		sf->Render();
	}
	if(_turnLeft == false)
	_curSprite->Render(_x,_y);
	else _curSprite->RenderScaleX(_x,_y);
}

void Boss::CheckCollision(MyObject* obj)
{
	int size = _listFire.size();
	BossFire* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listFire[i];
		sf->CheckCollision(obj);
	}
	if(obj->_ID == EObject::MARIO)
	{
		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
			case Top:
				obj->_vy = -2.0f;
				if(obj->_turnLeft == true)
					obj->_vx = -10.0f;
				else obj->_vx = 10.0f;

				if(_State != hurt)
					Hp-=1;
				_State = hurt;
				_curSprite->SelectIndex(0);
				break;
			case Bottom:
				obj->_State = transform;
				if(GL_CurForm != 0)
					GL_NextForm = GL_CurForm - 1;
				if(GL_CurForm == 0)
				{
					obj->_vy = -2.0;
					obj->_State = beforedead;
					return;
				}
				break;
			case Right:
				obj->_State = transform;
				if(GL_CurForm != 0)
					GL_NextForm = GL_CurForm - 1;
				if(GL_CurForm == 0)
				{
					obj->_vy = -2.0;
					obj->_State = beforedead;
					return;
				}
				break;
			case Left:
				obj->_State = transform;
				if(GL_CurForm != 0)
					GL_NextForm = GL_CurForm - 1;
				if(GL_CurForm == 0)
				{
					obj->_vy = -2.0;
					obj->_State = beforedead;
					return;
				}
				break;
		}
	}
}

CRECT Boss::GetRect()
{
	return CRECT(_x, _y , _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height);
}

