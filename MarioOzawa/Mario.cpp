// tieu nun, fix all

#include "Mario.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "MapLoader.h"
#include "Writer.h"
#include "Turtle.h"
#include "BrickItem.h"
#include "Boss.h"


Mario::Mario(float x, float y)	: MyObject(x, y)
{
	_sprMarioSmaller = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioSmaller.png"), 40);
	_sprMarioLarger = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioLarger.png"), 40);
	_sprMarioFire = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioFire.png"), 40);
	_turnLeft = false;
	if((GL_CurForm == 0) && (GL_NextForm == 0))
	{
 		_curSprite = _sprMarioSmaller;
 
  		GL_CurForm = 0;
		GL_NextForm = 1;
	}
	else
	{
		if(GL_CurForm == 1)
			_curSprite = _sprMarioLarger;
		else if(GL_CurForm == 2)
			_curSprite = _sprMarioFire;
		else _curSprite = _sprMarioSmaller;
	}
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	_State = stand;
	_startx = _x = x;
	_starty = _y = y;
	_vx = 0;
	_vy = 0;
	_TimeTransform = 0;
	_TimeFire = MARIO_FIRE_TIME;
	_ID = EObject::MARIO;

	life = 3;
	gold = 0;
	exp = 0;
}

Mario::~Mario(void)
{
	delete _sprMarioSmaller;
	delete _sprMarioLarger;
	delete _sprMarioFire;

	_sprMarioSmaller = NULL;
	_sprMarioLarger = NULL;
	_sprMarioFire = NULL;
}

void Mario::Update(int time)
{
	/*
	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Update(time);
	}

	Transform();

	_time = time;
	float _NextX = _x + _vx ;
	float _NextY = _y + _vy * _time;

	_vy += GRAVITY * time;
	CheckTitleCollision(_vx,_vy,_NextX,_NextY, GL_Width, GL_Height, _curSprite->_texture->Width,_curSprite->_texture->Height);

	//beforedead -> dead
	if(_State == beforedead)
	{
		_curSprite->SelectIndex(5);
		
		//check is dead
		if(_y > FALL_DEAD_HIGH * GL_MapH)
		{
			_State = dead;

			//reborn
			if(this->life > 0)
			{
				this->life--;
				this->_State = stand;

				this->_vx = 0;
				this->_vy = 0;

				this->_y = _starty; //MapLoader::_mariox * TILE;
				this->_x = _startx; //MapLoader::_mariox * TILE;
			}
		}

		return;
	}
	else //dead when fall out of map
	{
		if(_y > GL_MapH && _State != dead && _State != beforedead && _State != beforedead2)
		{
			_State = beforedead;
			this->_vy = -2.5f;
		}
	}

	if(_vx != 0)
	{
		_curSprite->Update(time);
	}
	if(_State == transform)
		return;

	// do when change dir suddenly
	if((_turnLeft == true) && (_vx > 0.0f))
		_curSprite->SelectIndex(4);
	if((_turnLeft == false) && (_vx < 0.0f))
		_curSprite->SelectIndex(4);

	if(_State == jumping){
		_curSprite->SelectIndex(3);
	}

	{//do not run out of the map
		//right
		if(_x + this->_curSprite->_texture->Width >= GL_MapW)
		{
			_x = GL_MapW - this->_curSprite->_texture->Width;
		}

		//left
		if(_x <= 0)
		{
			_x = 0;
		}
	}

	//save last position
// 	if(_State == stand || _State == Move)
// 	{
// 		if(abs(_x - _lastx) >= DISTANCE_WITH_LAST_POSITION_X)
// 		{
// 			_lastx = _x;
// 			_lasty = _y;
// 		}
// 	}
	*/
}

void Mario::Render()
{
	//tan long
	//reborn: draw a blur sprite
	if(_State == State::reborn)
		_curSprite->_color = D3DCOLOR_ARGB(100, 255, 255, 255);
	else
		_curSprite->_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	if(_turnLeft == false)
		_curSprite->Render((int)_x, (int)_y + 2); // for beautiful
	else 
		_curSprite->RenderScaleX((int)_x, (int)_y + 2); // for beautiful

	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Render();
	}
}

void Mario::TurnRight()
{
	if(_State == beforedead)
		return;

	// if press Right, Update _vx
	_vx += FRICTION_X * _time;
	if(_vx >= MAX_MARIO_VX)
		_vx = MAX_MARIO_VX;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	if((_State != transform) && (_State != Move) && (_State != jumping) && (_State != reborn))
	{
		_State = Move;
	}
	_turnLeft = false;
}

void Mario::TurnLeft()
{
	if(_State == beforedead)
		return;

	// if press Left, Update _vx
	_vx -= FRICTION_X * _time;
	if(_vx <= - MAX_MARIO_VX)
		_vx = - MAX_MARIO_VX;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	if((_State != transform) && (_State != Move) && (_State != jumping) && (_State != reborn))
	{
		_State = Move;
	}
	_turnLeft = true;
}

void Mario::Jump()
{
	if(_State == beforedead)
		return;

	//if(abs(_vy) < 0.2f && (_State != transform)){
	//	_State = jumping;
	//	_vy = - MARIO_VY;

	//	//sound
	//	SoundManager::GetInst()->PlayEffSound(SOUND_E_JUMP);
	//}

	if((abs(_vy) < 0.2f) && (_State != jumping) && (_State != transform)){
		_State = jumping;
		_vy = - MARIO_VY;

		//sound
		SoundManager::GetInst()->PlayEffSound(SOUND_E_JUMP);
	}
}

void Mario::Stand()
{
	if(_State == beforedead)
		return;
	//Not Press , Update _vx to 0.0f
	if(_vx < 0.0f)
		_vx += FRICTION_X/2 * _time;
	else if(_vx > 0.0f) _vx -= FRICTION_X/2 * _time;
	if((_vx <= 0.1f) && (_vx >= - 0.1f))
		_vx = 0.0f;

	//then set Stand frame
	if((_State != jumping) && (_State != transform) && (_vx == 0.0f) && (_State != reborn)){
		_State = stand;
		//_vx = 0;
		_curSprite->SelectIndex(0);
	}
}

//tan long
void Mario::ShitDown()
{
	if(_curSprite == _sprMarioLarger && _State == stand)
	{
		_vx = 0;
		_curSprite->SelectIndex(5);
	}
	else
	{
		//nothing
	}
}

void Mario::RunBeforeDie()
{
	_State = beforedead;
	this->_vy = -2.5f;
}

void Mario::Transform()
{
	if(_State == beforedead)
		return;

	if(_State == transform)
	{
		_TimeTransform++;
		if(_TimeTransform % 5 == 0)
		{
			if(GL_NextForm == 0)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioSmaller;
				_curSprite->SelectIndex(_tempIndex);
				//_y += 50;
				if(GL_CurForm == 1)
				{
					_y += 28;
				}
			}
			if(GL_NextForm == 1)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioLarger;
				_curSprite->SelectIndex(_tempIndex);
				if(GL_CurForm == 0)
				{
					_y -= 28;
					if((_State == transform) && (_turnLeft == false))
					{
						//_x -= 100;
					}
				}
			}
			if(GL_NextForm == 2)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioFire;
				_curSprite->SelectIndex(_tempIndex);
			}
		}
		else
		{
			if(_TimeTransform % 5 == 2)
			{
				if(GL_CurForm == 0)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite = _sprMarioSmaller;
					_curSprite->SelectIndex(_tempIndex);
					//_y += 50;
					if(GL_NextForm == 1)
					{
						_y +=28;
						if((_State == Move) && (_turnLeft == false))
						{
							//_x += 100;
						}
					}
				}
				if(GL_CurForm == 1)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite =_sprMarioLarger;
					_curSprite->SelectIndex(_tempIndex);
					if(GL_NextForm == 0)
					{
						_y -= 28;
					}
					//_y -= 50;
				}
				if(GL_CurForm == 2)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite = _sprMarioFire;
					_curSprite->SelectIndex(_tempIndex);
				}
			}
		}

		if(_TimeTransform == 30)
		{
			_TimeTransform = 0;
			GL_CurForm = GL_NextForm;
			if(_vy == 0)
				_State = stand;
			else _State = jumping;
		}
	}
}

void Mario::TransformMario(int x, int y)
{
	_State = transform;
	GL_CurForm = x;
	GL_NextForm = y;
	//if((GL_CurForm == 0) && (GL_NextForm == 1))
	//	_y -= 40;

	//SOUND
	SoundManager::GetInst()->PlayEffSound(SOUND_E_GROW);
}

void Mario::CheckCollision(MyObject* obj)
{
	int size = _listBullet.size();

	bullet* sf;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->CheckCollision(obj);
	}

	//check collision mario
	if(_State == beforedead || _State == dead || _State == beforedead2 || _State == reborn)
		return;

	if((obj->_ID == EObject::FUNGI) || (obj->_ID == EObject::TURTLE))
	{
		if(_State == transform)
			return;
		if(_State == reborn)
			return;
		if(obj->_State == dead)
			return;

		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Bottom:
			{
				if(obj->_ID == EObject::FUNGI && obj->_State == beforedead2)
				{
				}
				else
				{
					_vy = -1.5;
					_State = jumping;

					//tan long
					//add exp
					exp += EXP_FOR_OBJECT;

					//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);
				}
			}				
			break;
		}
	}
}

CRECT Mario::GetRect()
{
	return CRECT(
		_x, //+ DELTA_RECT_X, 
		_y, //+ DELTA_RECT_Y, 
		_x + _curSprite->_texture->Width,// - 2 * DELTA_RECT_X, 
		_y + _curSprite->_texture->Height);// - 2 * DELTA_RECT_Y);
}

CRECT Mario::GetRect1()
{
	return CRECT(
		_x + DELTA_RECT_X + 5, 
		_y + DELTA_RECT_Y, 
		_x + _curSprite->_texture->Width - 2 * DELTA_RECT_X - 10, 
		_y + _curSprite->_texture->Height - 2 * DELTA_RECT_Y);
}

void Mario::Fire()
{
	if(GL_CurForm != 2)
		return;

	if(_TimeFire <= MARIO_FIRE_TIME)
		return;

	if((_State == stand) || (_State == jumping) || (_State == Move))
	{
		//sound
		SoundManager::GetInst()->PlayEffSound(SOUND_E_SHOT, false);

		bullet* sf;
		if(_turnLeft == true)
			sf = new bullet(_x - 30,_y + 35,_turnLeft);
		else sf = new bullet(_x + 50,_y + 35,_turnLeft);
		_listBullet.push_back(sf);
		_TimeFire = 0;
	}
}

void Mario::UpdateRealTimeCollision(int time, vector<MyObject*>* listcollision)
{
	//////////////////////////////////////////////////////////////////////////
	//bullet update + collision
	_listCollisionData.clear();
	int size = _listBullet.size();

	bullet* sf;
	bool _deadListBullet = true;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		if(sf->_State != dead)
			_deadListBullet = false;
		//sf->Update(time);
		sf->UpdateRealTimeCollision(time, listcollision);
	}

	if(_deadListBullet == true)
		_listBullet.clear();
	//////////////////////////////////////////////////////////////////////////
	_TimeFire += time;
	Transform();

	//xet hinh dang mario so voi trang thai
	if(_State != transform)
	{
		if(GL_CurForm == 0)
			_curSprite = _sprMarioSmaller;
		if(GL_CurForm == 1)
			_curSprite = _sprMarioLarger;
		if(GL_CurForm == 2)
			_curSprite = _sprMarioFire;
	}
	//
	
	//mer
	static int timeReborn = TIME_REBORN + 1;
	
	if(_State != beforedead)
		_nextx = _x + _vx * _time;
	else 
		_nextx = _x;

	_nexty = _y + _vy * _time;
	
	int size1 = listcollision->size();

	//MyObject* temp;
	//mer
	//new tan long
	if((_State != beforedead) && (_State != dead))
	{
		for(int k = 0 ; k < size1; ++k)
		{
			//////////////////////////////////////////////////////////////////////////
			if(listcollision->at(k)== this)
				continue;
			//////////////////////////////////////////////////////////////////////////

			if((listcollision->at(k)->_State == dead) || (listcollision->at(k)->_State == beforedead) || (listcollision->at(k)->_State == beforedead2))
				continue;
			if((listcollision->at(k)->_ID == EObject::TURTLE) || (listcollision->at(k)->_ID == EObject::BRICKBREAK) || (listcollision->at(k)->_ID == EObject::TREEMONSTER))
			{
				this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,_time);
			}
			else 
				/*if((listcollision->at(k)->_ID == EObject::BRICKITEM) && (listcollision->at(k)->_State != hasItem))
				{
					this->RealTimeCollisionWithItem(this->GetRect1(),(brickItem*)listcollision->at(k),k,_time);
					this->RealTimeCollision1(this->GetRect1(),listcollision->at(k),k,_time);
				}
				else*/ this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,_time);
		}
	}

	bool check = _listCollisionData.check();

	//if(_State != reborn)
	if(check == true) // co va cham
	{
		bool backPosition = false;
		int a = _listCollisionData._listNewData.size();
		for(int m = 0;m < _listCollisionData._listNewData.size();m++)
		{
			int index = _listCollisionData._listNewData.at(m)->_indexObject;
			int idobject = _listCollisionData._listNewData.at(m)->_ID;
			EDirect dir = _listCollisionData._listNewData.at(m)->_dirCollision;
			State stateObject = listcollision->at(index)->_State;

			if(backPosition == false)
			{
				if((idobject == EObject::BRICKBREAK) || (idobject == EObject::BRICKITEM) || (idobject == EObject::BRICKQUESTION))
				{
					// newwwwwwwwwwwwwwww
					_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
					_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
					if(dir == Top)
						_vy = 0.0f;
					if(dir == Bottom)
						_vy = 0.0f;
					backPosition = true;
				}
			}

			//////////////////////////////////////////////////////////////////////////
			if(idobject == EObject::BRICKBREAK)
			{
				if((stateObject == breaking) || (stateObject == dead))
					break;
				if(_State == reborn)
					continue;
				if(dir == Top)
				{
					//add exp
					exp += EXP_FOR_BRICK;

					_vy = 0.0f;
					if(GL_CurForm == 0)
					{
						//break;
						listcollision->at(index)->_State = Move;
						continue;
					}
					listcollision->at(index)->_State = breaking;
					SoundManager::GetInst()->PlayEffSound(SOUND_E_BROKEN);
					continue;
				}

				if(dir == Bottom)
				{
					_vy = 0.0f;
					if((_State != transform) && (_State != reborn))
						_State = stand;
					continue;
				}
			}

			//////////////////////////////////////////////////////////////////////////
			if(idobject == EObject::BRICKQUESTION)
			{
				if(_State == reborn)
					continue;
				if(dir == Top)
				{
					//add exp
					exp += EXP_FOR_BRICK;

					_vy = 0.0f;
					if(stateObject == hasCoin)
					{
						listcollision->at(index)->_State = noCoin;
						//listcollision->at(index)->_curSprite->SelectIndex(0);
						this->gold++;
						SoundManager::GetInst()->PlayEffSound(SOUND_E_COIN);
						continue;
					}
				}
				if(dir == Bottom)
				{
					_vy = 0.0f;
					if((_State != transform) && (_State != reborn))
						_State = stand;
					continue;
				}
			}

			//////////////////////////////////////////////////////////////////////////
			if(idobject == EObject::BRICKITEM)
			{
				if(_State == reborn)
					continue;
				if(dir == Top)
				{
					//add exp
					exp += EXP_FOR_BRICK;

					_vy = 0.0f;
					if(stateObject != hasItem)
						continue;
					listcollision->at(index)->_State = stand;
					((brickItem*)listcollision->at(index))->_curSprite->SelectIndex(0);
					//Item *_xx = new Item(listcollision->at(index)->_x,listcollision->at(index)->_y,EBrickItemKind::FLOWER);
					QuadTree::Insert(((brickItem*)listcollision->at(index))->_item);
					//QuadTree::Insert(_xx);
					//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_UP);
					continue;
				}
			}

			if(idobject == EObject::COIN)
			{
				if(stateObject == dead)
					continue;
				if(_State == reborn)
					continue;
				listcollision->at(index)->_State = dead;
				// tien tang
				this->gold++;
				//sound
				SoundManager::GetInst()->PlayEffSound(SOUND_E_COIN);
				continue;
			}

			if(idobject == ITEM)
			{
				if(_State == reborn)
					continue;
				listcollision->at(index)->_State = dead;
				if( ((Item*)listcollision->at(index))->_item != SHOOTER )
				{
					if(GL_CurForm != 2)
					{
						_State = transform;
						GL_NextForm = GL_CurForm + 1;
						if((GL_CurForm == 0) && (GL_NextForm == 1))
							_y -= 50;
					}// player transform or + heart khi nhat dc item here*/
				}
				else 
					this->life++;
			}

			if(idobject == EObject::TREEMONSTER)
			{
				_State = transform;
				if(GL_CurForm != 0)
					GL_NextForm = GL_CurForm - 1;
				if(GL_CurForm == 0)
				{
					_vy = -2.0;
					_State = beforedead;
				}
				continue;
			}

			if(idobject == EObject::FUNGI)
			{
				if(_State == transform || _State == reborn)
					continue;

				if((stateObject == dead) || (stateObject == beforedead) || (stateObject == beforedead2))
					continue;
				if(dir == Bottom)
				{
					_vy = -1.5;
					_State = jumping;
					listcollision->at(index)->_State = beforedead;
				//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);
					if(backPosition == false)
					{
						{
							_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
							_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
							backPosition = true;
						}
					}
					continue;
				}
				else
				{
					_State = transform;
					if(GL_CurForm != 0)
						GL_NextForm = GL_CurForm - 1;
					if(GL_CurForm == 0)
					{
						_vy = -2.0;
						_State = beforedead;
					}
					continue;
				}
			}

			if(idobject == EObject::BOSS)
			{
				if(dir == Bottom)
				{
					_vy = -2.0f;
					if(_turnLeft == true)
						_vx = -8.0f;
					else _vx = 8.0f;

					if(listcollision->at(index)->_State != hurt)
						((Boss*)listcollision->at(index))->Hp-=1;
					listcollision->at(index)->_State = hurt;
					((Boss*)listcollision->at(index))->_curSprite->SelectIndex(0);
				}
				else
				{
					_State = transform;
					if(GL_CurForm != 0)
						GL_NextForm = GL_CurForm - 1;
					if(GL_CurForm == 0)
					{
						_vy = -2.0;
						_State = beforedead;
					}
					continue;
				}
			}

			if(idobject == EObject::TURTLE)
			{
				if(_State == transform || _State == reborn)
					continue;

				if(stateObject == dead)
					continue;

				if(dir == Bottom)
				{
					if((stateObject == stand) || (stateObject == attack))
					{
						_nexty += 10;
					}
					_vy = -1.5;
					_State = jumping;
					//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);

					if(backPosition == false)
					{
						{
							_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
							_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
							backPosition = true;
						}
					}
					if((stateObject == Move) || (stateObject == attack))
					{
						listcollision->at(index)->_State = stand;
						//(turtle*)listcollision->at(index)->_curSprite->SelectIndex(2);
						((turtle*)listcollision->at(index))->_curSprite->SelectIndex(2);
						((turtle*)listcollision->at(index))->_TimeStand = 0;
						((turtle*)listcollision->at(index))->_TimeAttack = 0;
					}
					continue;
				}

				if(dir != EDirect::Bottom)
				{
					if((stateObject == Move) || (stateObject == attack))
					{
						if(((turtle*)listcollision->at(index))->_TimeAttack < 15)
							continue;
						/*
						obj->_State = transform;
						// player bi mat mau
						// set next form
						*/
						_State = transform;
						if(GL_CurForm != 0)
							GL_NextForm = GL_CurForm - 1;
						if(GL_CurForm == 0)
						{
							_vy = -2.0;
							_State = beforedead;
							break;
						}
						continue;
					}
				}

				if((dir == Right) || (dir == Left))
				{
					if((stateObject == stand) && (((turtle*)listcollision->at(index))->_TimeStand > 20))
					{
						((turtle*)listcollision->at(index))->_curSprite->_start = 2;
						((turtle*)listcollision->at(index))->_curSprite->_start = 4;
						listcollision->at(index)->_State = attack;
						((turtle*)listcollision->at(index))->_TimeAttack = 0;
						if(dir == Left)							
							listcollision->at(index)->_turnLeft = true;
						if(dir == Right)
							listcollision->at(index)->_turnLeft = false;
						continue;
					}
				}
			}
		}
	} 
			
	_vy += GRAVITY * time;
	_time = time;
	CheckTitleCollision(_vx,_vy,_nextx,_nexty, GL_Width, GL_Height, _curSprite->_texture->Width,_curSprite->_texture->Height);
	//if(_vy != 0.0f)
	//	int S = 0;
	_x = _nextx;
	_y = _nexty;

	//beforedead -> dead
	if(_State == beforedead)
	{
		_curSprite->SelectIndex(5);
		
		//check is die
		if(_y > FALL_DEAD_HIGH * GL_MapH)
		{
			_State = dead;

			//sound
			//SoundManager::GetInst()->PlayEffSound(SOUND_E_DEATH, false);

			//reborn
			if(this->life > 0)
			{
				timeReborn = 0;

				this->life--;
				this->_State = stand;

				this->_vx = 0;
				this->_vy = -2.0f;

				this->_y = _starty; //MapLoader::_mariox * TILE;
				this->_x = _startx; //MapLoader::_mariox * TILE;

				this->Jump();

				_State = reborn;
			}
		}

		return;
	}
	else //dead when fall out of map
	{
		if(_y > GL_MapH && _State != dead && _State != beforedead && _State != beforedead2)
		{
			RunBeforeDie();
			//_State = beforedead;
			//this->_vy = -2.5f;
		}
	}

	//mer
	//reborn state
	timeReborn += _time;
	if(timeReborn < TIME_REBORN)
	{
		_State = reborn;
	}else
	{
		timeReborn = TIME_REBORN + 1;
	}

	//new tan long//
	if(abs(_vy) >= 0.2f && _State != reborn && _State != beforedead && _State != beforedead2 && _State != dead && _State != transform)
	{
		_State = jumping;
	}

	//update sprite
	if(_vx != 0)
	{
		_curSprite->Update((int)((float)time * (float)abs(_vx) / (float)MAX_MARIO_VX));
	}

	if(_State == transform)
		return;

	// do when change dir suddenly
	if((_turnLeft == true) && (_vx > 0.0f))
		_curSprite->SelectIndex(4);

	if((_turnLeft == false) && (_vx < 0.0f))
		_curSprite->SelectIndex(4);

	if(_State == jumping){
		_curSprite->SelectIndex(3);
	}
	if((_State == reborn)&&(_vx == 0.0f)&&(_vy == 0.0f))
	{
		_curSprite->SelectIndex(0);
	}

	//save last position
	if(_State == State::stand || _State == State::Move || _State == State::alive)
	{
		if(abs(_x - _startx) >= DISTANCE_WITH_LAST_POSITION_X)
		{
			_startx = _x;
			_starty = _y;
		}
	}
}

void Mario::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if((_State == beforedead) || (_State == dead))
	{
		//_x = _nextX;
		_nextY = _nextY;
		return;
	}
	bool jump = true;
	if (_vy >= 0.0f){
		// DOWN
		_nextY ;
		bool iColTer = false;
		for (int j = (_y + _height)/TILE; j <=  (_nextY+_height + 1)/TILE ;j++){
			for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
			if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					//if(checkY == false)
					{
						jump = false;
						this->_vy = 0;
						iColTer = true;
						_nextY = TILE * (j) - _height - 1 ;
						if((_State != transform) && (_State != reborn))
							_State = stand;
						break;
					}
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			_nextY = _nextY ;
		}

	}else{
		// UP
		int n = (_nextY/TILE);
		int m = (_y/TILE);
		if (n!=m ){

			bool iColTerY = false;
			for (int j = _y/TILE-1; j >  _nextY/TILE-1;j--){
				for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						//if(checkY == true)
						{
							jump = false;
							iColTerY = true;
							_nextY = TILE * (j+1);
							_vy = 0;//fabs(_vy);
							break;
						}
					}
				}
				if (iColTerY == true){
					break;
				}
			}

			if (iColTerY == false){
				_nextY = _nextY;
			}

		}else{
			_nextY = _nextY;
		}
	}
	if((_State != transform) && (_State != dead) && (_State != beforedead) && (_State != beforedead2))
	{
		if(jump == true)
			_State = jumping;
	}

	if (_vx > 0)
	{
		bool iColTerX1 = false;
		for (int i = (_x + _width)/TILE ; i <  (_nextX+_width)/TILE;i++)
		{
			for (int j = _y/TILE;j < (int)((_y+_height-1)/TILE) +1;j++ )
			{
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					iColTerX1 = true;
					_nextX = TILE * (i) - _width;
					break;
				}
			}
			if (iColTerX1 == true)
			{
				break;
			}
		}

		if (iColTerX1 == false){
			_nextX = _nextX;
		}

	}
	else
	{
		if (_vx <= 0){

			if (_nextX <= 0)
			{
				_nextX = 0;
			}
			bool iColTerX2 = false;
			for (int i = _x/TILE-1; i >  _nextX/TILE-1;i--) // 
			{
				for (int j = _y/TILE ;j < int((_y+_height-1)/TILE) +1 ; j++ )
				{
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						iColTerX2 = true;
						_nextX = TILE * (i+1);
						break;
					}
				} 
				if (iColTerX2 == true)
				{
					break;
				}
			}

			if (iColTerX2 == false)
			{
				_nextX = _nextX;
			}

		}		
	}
}