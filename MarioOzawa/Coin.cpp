
#include "SoundManager.h"
#include "Coin.h"
#include "ResourceManager.h"
#include "Mario.h"

coin::coin(float x, float y,State state)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Coin.png"), 100);
	_ID = EObject::COIN;
	if(state == State::start)
		_State = stand;
	else _State = state;
}

coin::~coin(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void coin::Update(int time)
{
	if(_State == dead)
		return;
	_curSprite->Update(time);
}

void coin::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x, (int)_y);
}

void coin::CheckCollision(MyObject* obj)
{
	/*
	if(_State == dead)
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if(this->GetCollisionDirection(obj->GetRect(), this->GetRect()) != None)
		{
			_State = dead;
			// tien tang
			((Mario*)obj)->gold++;

			//sound
			SoundManager::GetInst()->PlayEffSound(SOUND_E_COIN);
		}
	} */
}

CRECT coin::GetRect()
{
	//return CRECT(_x + 12, _y, _x + _curSprite->_texture->Width - 24, _y + _curSprite->_texture->Height);
	return CRECT(_x , _y, _x + _curSprite->_texture->Width, _y + _curSprite->_texture->Height);

}