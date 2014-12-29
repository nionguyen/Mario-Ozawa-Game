
#include "SoundManager.h";
#include "Turtle.h"
#include "ResourceManager.h"
#include "TileMap.h"

turtle::turtle(float x, float y,State state)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/turtle.png"), 90);
	_curSprite->_start = 0;
	_curSprite->_end = 1;
	_x = x;
	_y = y;
	_vx = 0;
	_vy = 0;
	_turnLeft = true;
	_ID = EObject::TURTLE;
	if(state == State::start)
		_State = Move;
	else _State = state;
	_TimeStand = 0;
	_TimeAttack = 0;
}


turtle::~turtle(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void turtle::Render()
{
	if(_State == dead)
		return;

	if(_State == beforedead2)
	{
		_curSprite->RenderScaleY((int)_x, (int)_y);
		return;
	}

	if(_State == attack)
	{
		_curSprite->SelectIndex(2);
	}

	if(_turnLeft == false)
	{
		if((_State == attack) || (_State == stand))
			_curSprite->Render((int)_x, (int)_y + 25 );
		else 
			_curSprite->Render((int)_x, (int)_y);
	}
	else
	{
		if((_State == attack) || (_State == stand))
			_curSprite->RenderScaleX((int)_x, (int)_y + 25);
		else 
			_curSprite->RenderScaleX((int)_x, (int)_y);
	}
}

void turtle::Update(int time)
{
	//return;
	//
	//if(_State == dead)
	//	return;

	//_listCollisionData.clear();
	//
	//if(_y >= 800)
	//	_State = dead;

	//if(_State == stand)
	//{
	//	_curSprite->SelectIndex(2);
	//	_TimeStand++;
	//	//return;
	//}
	//
	//if(_State == beforedead2)
	//	_curSprite->SelectIndex(2);
	//
	//if((_State == attack) || (_State == Move))
	//	_TimeAttack++;
	//
	//_nextx = _x + _vx * time;
	//_nexty = _y + _vy * time;

	//_vy += GRAVITY * time;
	//CheckTitleCollision(_vx,_vy,_nextx,_nexty,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height);
	//_x = _nextx;
	//_y = _nexty;
	//if(_State != beforedead2)
	//{
	//	if((_State == Move) || (_State == attack))
	//	{
	//		if(_turnLeft == true)
	//		{
	//			if(_State == Move)
	//				_vx = -0.1;
	//			if(_State == attack)
	//				_vx = -0.7;
	//		}
	//		else
	//		{
	//			if(_State == Move)
	//				_vx = 0.1;
	//			if(_State == attack)
	//				_vx = 0.7;
	//		}
	//	}
	//	else _vx = 0;
	//}

	//if(_State == Move)
	//	_curSprite->Update(time);

}

void turtle::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	if(_State == dead)
		return;
	
	_listCollisionData.clear();
	if(_y >= 800)
		_State = dead;
	if(_State == stand)
	{
		_curSprite->SelectIndex(2);
		_TimeStand++;
		//return;
	}
	if(_State == beforedead2)
		_curSprite->SelectIndex(2);
	if((_State == attack) || (_State == Move))
		_TimeAttack++;

	_nextx = _x + _vx * time;
	_nexty = _y + _vy * time;


	int size1 = listcollision->size();

	if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
	{
		for(int k = 0 ; k < size1; ++k)
		{
			if(listcollision->at(k) == this)
				continue;
			if(listcollision->at(k)->_ID == EObject::MARIO)
			{
				//this->RealTimeCollision1(this->GetReSizeRect2(),listcollision->at(k),k,time);
				this->RealTimeCollision1(this->GetReSizeRect1(),listcollision->at(k),k,time);
			}
			if((listcollision->at(k)->_ID == EObject::TURTLE) || (listcollision->at(k)->_ID == EObject::FUNGI) || (listcollision->at(k)->_ID == EObject::BRICKBREAK))
			{
				if(_State != attack)
					this->RealTimeCollision1(this->GetReSizeRect3(),listcollision->at(k),k,time);
				else this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
			}
			/*if(listcollision->at(k)->_ID == EObject::FUNGI)
			{
				if(_State != attack)
					this->RealTimeCollision1(this->GetReSizeRect3(),listcollision->at(k),k,time);
				else this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
			}*/
		}
	}
	bool check = _listCollisionData.check();
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
				if(((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE)) && ((dir == Left) || (dir == Right)))
				{
					if(_State != attack)
					{
						_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
						_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
						backPosition = true;
					}
				}
			}
			if(idobject == EObject::MARIO)
			{
				if(stateObject == reborn)
					continue;
				if((dir == Left) || (dir == Right) || (dir == Bottom))
				{
					if((_State == Move) || (_State == attack))
					{
						if(_TimeAttack < 15)
							continue;
						/*
						obj->_State = transform;
						// player bi mat mau
						// set next form
						*/
						listcollision->at(index)->_State = transform;
						if(GL_CurForm != 0)
							GL_NextForm = GL_CurForm - 1;
						if(GL_CurForm == 0)
						{
							listcollision->at(index)->_vy = -2.0;
							listcollision->at(index)->_State = beforedead;
							continue;
						}
						continue;
					}
					
					if((_State == stand) && (_TimeStand > 20))
					{
						if(dir == Bottom)
							continue;
						_curSprite->_start = 2;
						_curSprite->_start = 4;
						_State = attack;
						_TimeAttack = 0;
						if(dir == Left)
						_turnLeft = false;
						if(dir == Right)
						_turnLeft = true;
						continue;
					}
				}
			}
			if(idobject == BRICKBREAK)
			{
				if(stateObject == breaking)
				{
					_State = beforedead2;
					_vy = -0.85f;
				}
			}
			if((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE))
			{
				if(dir == Left)
				{	if(_State == attack)
					{
						listcollision->at(index)->_State = beforedead2;
						listcollision->at(index)->_vx = 0.2;
						listcollision->at(index)->_vy = -1.1;
						continue;
					}
					//_x = listcollision->at(index)->_x + TILE + 1;
					else
					{
						if(listcollision->at(index)->_State == State::attack)
							continue;
						_turnLeft = false;
						listcollision->at(index)->_turnLeft = true;
						continue;
					}
				}
				if(dir == Right)
				{
					if(_State == attack)
					{
						listcollision->at(index)->_State = beforedead2;
						listcollision->at(index)->_vx = -0.2;
						listcollision->at(index)->_vy = -1.1;
						continue;
					}
					//_x = listcollision->at(index)->_x - this->_curSprite->_texture->Width - 1;
					else
					{
						if(listcollision->at(index)->_State == State::attack)
							continue;
						_turnLeft = true;
						listcollision->at(index)->_turnLeft = false;
						continue;
					}
				}

			}
		}
	}

	_vy += GRAVITY * time;
	CheckTitleCollision(_vx,_vy,_nextx,_nexty,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height);
	
	_x = _nextx;
	_y = _nexty;

	if(_State != beforedead2)
	{
		if((_State == Move) || (_State == attack))
		{
			if(_turnLeft == true)
			{
				if(_State == Move)
					_vx = -0.1;
				if(_State == attack)
					_vx = -0.7;
			}
			else
			{
				if(_State == Move)
					_vx = 0.1;
				if(_State == attack)
					_vx = 0.7;
			}
		}
		else _vx = 0;
	}

	if(_State == Move)
		_curSprite->Update(time);
}


void turtle::CheckCollision(MyObject* obj)
{
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == transform) || (obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == reborn))
			return;
		switch(this->GetCollisionDirection(this->GetReSizeRect1(), obj->GetRect()))
		{
		case Top:
			if((_State == Move) || (_State == attack))
			{
				_State = stand;
				_curSprite->SelectIndex(2);
				_TimeStand = 0;
				_TimeAttack = 0;
			}
			break;
		case  Left:
			if((_State == Move) || (_State == attack))
			{
				if(_TimeAttack < 15)
					return;
				/*
				obj->_State = transform;
				// player bi mat mau
				// set next form
				*/
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
			break;
		case Right:
			if((_State == Move) || (_State == attack))
			{
				if(_TimeAttack < 15)
					return;
				/*
				obj->_State = transform;
				// player bi mat mau
				// set next form
				*/
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
			break;
		case Bottom:
			if((_State == Move) || (_State == attack))
			{
				if(_TimeAttack < 20)
					return;
				/*
				obj->_State = transform;
				// player bi mat mau
				// set next form
				*/
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
			break;
		}
	}

	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == transform) || (obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == reborn))
			return;
		switch(this->GetCollisionDirection(this->GetReSizeRect2(), obj->GetRect()))
		{
		case  Left:
			if((_State == stand) && (_TimeStand > 20))
			{
				_curSprite->_start = 2;
				_curSprite->_start = 4;
				_State = attack;
				_TimeAttack = 0;
				_turnLeft = false;
			}

			break;
		case  Right:
			if((_State == stand) && (_TimeStand > 20))
			{
				_curSprite->_start = 2;
				_curSprite->_start = 4;
				_turnLeft = true;
				_State = attack;
				_TimeAttack = 0;
			}
			break;
		}
	}
}

// va cham voi mario : mario xu ly
CRECT turtle::GetRect()
{
	return CRECT(_x - 7, _y + 15, _x + _curSprite->_texture->Width + 14, _y + _curSprite->_texture->Height - 15);
	//return CRECT(_x, _y + 15 , _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height - 15);
}

// va cham voi mario : rua xu ly
CRECT turtle::GetReSizeRect1()
{
	return CRECT(_x - 7, _y + 10, _x + _curSprite->_texture->Width + 14, _y + _curSprite->_texture->Height - 10);
}


// va cham voi mario : rua xu ly
CRECT turtle::GetReSizeRect2()
{
	return CRECT(_x - 5, _y - 40, _x + _curSprite->_texture->Width + 10, _y + _curSprite->_texture->Height + 40);
}


// va cham voi object tinh, va voi object dong # : rua, nam
CRECT turtle::GetReSizeRect3()
{
	return CRECT(_x, _y , _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height );
}

void turtle::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if((_State == beforedead2) || (_State == beforedead) || (_State == dead))
	{
		_nextX = _nextX;
		_nextY = _nextY;
		return;
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
					_turnLeft = true;
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
						_turnLeft = false;
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

	if (_vy >= 0){
		// DOWN
		bool iColTer = false;
		for (int j = (_y + _height)/TILE; j <  (_nextY+_height)/TILE ;j++){
			for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					//if(checkY == false)
					{
						iColTer = true;
						_nextY = TILE * (j) - _height;
						//_State = stand;
						_vy = 0;
						break;
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
}