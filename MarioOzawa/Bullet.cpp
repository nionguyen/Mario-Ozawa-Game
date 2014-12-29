#include "Bullet.h"
#include "ResourceManager.h"
#include "TileMap.h"


bullet::bullet(float x, float y,bool turnLeft) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Bullet.png"), 100);
	_curSprite->_start = 0;
	_curSprite->_end = 3;
	_vx = 0;
	_vy = 0;
	_turnLeft = turnLeft;
	_State = Move;
}

bullet::~bullet(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void bullet::Update(int time)
{
	/*if(_State == dead)
		return;

	if(_State == Move)
	{
		
		float _NextX;
		float _NextY; 
		_NextX = _x + _vx * time;
		_NextY = _y + _vy * time;

		CheckTitleCollision(_vx,_vy,_NextX,_NextY,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height - 10);
		if(_turnLeft == true)
			_vx = -0.8;
		else _vx = 0.8;
		_vy = this->_vy + 0.055 ;
	}
	_curSprite->Update(time);*/
}

void bullet::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	if(_State == dead)
		return;
	_listCollisionData.clear();
	if(_State == Move)
	{
		_nextx = _x + _vx * time;
		_nexty = _y + _vy * time;
		
			int size1 = listcollision->size();

	if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
	{
		for(int k = 0 ; k < size1; ++k)
		{
			if(listcollision->at(k) == this)
				continue;
			if((listcollision->at(k)->_ID == EObject::FUNGI) || (listcollision->at(k)->_ID == EObject::TURTLE) || (listcollision->at(k)->_ID == EObject::BOSS))
				this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
		}
	}
	bool check = _listCollisionData.check();
	if(check == true) // co va cham
	{
		//bool backPosition = false;
		int a = _listCollisionData._listNewData.size();
		for(int m = 0;m < _listCollisionData._listNewData.size();m++)
		{
			int index = _listCollisionData._listNewData.at(m)->_indexObject;
			int idobject = _listCollisionData._listNewData.at(m)->_ID;
			EDirect dir = _listCollisionData._listNewData.at(m)->_dirCollision;
			State stateObject = listcollision->at(index)->_State;
			/*
			if(backPosition == false)
			{
				if(((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE)) && ((dir == Left) || (dir == Right)))
				{
					//if(_State == attack)
					//	break;
					_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
					_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
					backPosition = true;
				}
			}*/
			if((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE))
			{
				if((listcollision->at(index)->_State == dead) || (listcollision->at(index)->_State == beforedead) || (listcollision->at(index)->_State == beforedead2)) 
					break;
				else
				{
					listcollision->at(index)->_State = beforedead2;
					if(this->GetCollisionDirection(this->GetRect(), listcollision->at(index)->GetRect()) == Left)
						listcollision->at(index)->_vx = 0.2;
					else listcollision->at(index)->_vx = -0.2;
					listcollision->at(index)->_vy = -1.1;
					_State = beforedead;
					_curSprite->_start = 7;
					_curSprite->_end = 9;
					_curSprite->_timeAni = 15;
				}
			}
			if(idobject == EObject::BOSS)
			{
				if((listcollision->at(index)->_State == dead) || (listcollision->at(index)->_State == beforedead) || (listcollision->at(index)->_State == beforedead2)) 
					break;
				else
				{
					_State = beforedead;
					_curSprite->_start = 7;
					_curSprite->_end = 9;
					_curSprite->_timeAni = 15;
				}
			}
		}
	}


	_vy = this->_vy + 0.1f; //0.055
	CheckTitleCollision(_vx,_vy,_nextx,_nexty,GL_Width,GL_Height,_curSprite->_texture->Width,_curSprite->_texture->Height - 10);
	_x = _nextx;
	_y = _nexty;
	if(_turnLeft == true)
		_vx = -1.6; //0.8
	else _vx = 1.6;
	}

	_curSprite->Update(time);
}

void bullet::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x, (int)_y);
	if(_curSprite->_index == 9)
		_State = dead;
}

void bullet::CheckCollision(MyObject* obj)
{
	if((_State == dead) || (_State == beforedead))
		return;
	
	if((obj->_ID == EObject::FUNGI) || (obj->_ID == EObject::TURTLE))
	{
		if((obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == beforedead2)) 
			return;
		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != None)
		{
			obj->_State = beforedead2;
			if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) == Left)
				obj->_vx = 0.2;
			else obj->_vx = -0.2;
			obj->_vy = -1.1;
			_State = beforedead;
			_curSprite->_start = 7;
			_curSprite->_end = 9;
			_curSprite->_timeAni = 15;
		}
	}
}

CRECT bullet::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height - 10);
}

void bullet::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	
	if((_State == beforedead) || (_State == dead))
		return;
	if (_vy >= 0)
	{
		// DOWN
		bool iColTer = false;
		for (int j = (_y + _height)/TILE; j <  (_nextY+_height)/TILE ;j++){
			for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					{
						iColTer = true;
						this->_vy = -0.6f;
						_nextY = TILE * (j) - (_curSprite->_texture->Height - 10 );
						return;
					}
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			_nextY = _nextY;
		}
	}

	if (_vx > 0)
	{
		if (_nextX >= (_maxWidth+100))
		{
			//_State = dead;
		}
		bool iColTerX1 = false;
		for (int i = (_x + _width)/TILE ; i <  (_nextX + _width)/TILE; i++)
		{
			for (int j = _y/TILE;j < (int)((_y+_height-1)/TILE) +1;j++ )
			{
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					iColTerX1 = true;
					_State = beforedead;
					_curSprite->_start = 7;
					_curSprite->_end = 9;
					_curSprite->_timeAni = 15;
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
		if (_vx <= 0)
		{
			if (_nextX <= -100)
			{
				_State = dead;
			}
			bool iColTerX2 = false;
			for (int i = _x/TILE-1; i >  _nextX/TILE-1;i--) // 
			{
				for (int j = _y/TILE ;j < int((_y+_height-1)/TILE) +1 ; j++ )
				{
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						_State = beforedead;
						_curSprite->_start = 7;
						_curSprite->_end = 9;
						_curSprite->_timeAni = 15;
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

	_nextY = _nextY;
	_nextX = _nextX;
}