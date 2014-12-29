#include "Fungi.h"
#include "ResourceManager.h"
#include "TileMap.h"

fungi::fungi(float x, float y,State state)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Fungi.png"), 50);
	_curSprite->_start = 0;
	_curSprite->_end = 1;
	_x = x;
	_y = y;
	_vx = 0;
	_vy = 0;
	_turnLeft = true;
	_timeTransform = 0;
	_ID = EObject::FUNGI;
	if(state == State::start)
		_State = Move;
	else _State = state;
}


fungi::~fungi(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void fungi::Update(int time)
{
	if(_State == dead)
		return;

	// neu roi wa khoi map
	if(_y >= 800)
		_State = dead;
	float _NextX;
	float _NextY;
	if(_State != beforedead)
	{
		_NextX = _x + _vx * time;
		_NextY = _y + _vy * time;
	}
	else
	{
		_NextX = _x;
		_NextY = _y;
	}
	if(_State == beforedead)
	{
		_curSprite->SelectIndex(2);
		_timeTransform += time;
		if(_timeTransform >= 150)
			_State = dead;
		return;
	}
	if(_State != beforedead2)
	{
		if(_turnLeft == true)
			_vx = -0.1;
		else _vx = 0.1;
	}
	
	_vy += GRAVITY * time;

	CheckTitleCollision(_vx,_vy,_NextX,_NextY,GL_Width,GL_Height,_curSprite->_texture->Width,_curSprite->_texture->Height);

	_curSprite->Update(time);
}

void fungi::Render()
{
	if(_State == dead)
		return;
	//if(_turnLeft == false)
	if(_State != beforedead2)
		_curSprite->Render((int)_x, (int)_y);
	if(_State == beforedead2)
		_curSprite->RenderScaleY((int)_x, (int)_y);
	//else _curSprite->RenderScale((int)_x, (int)_y);
}

void fungi::CheckCollision(MyObject* obj)
{	
	if((_State == beforedead) || (_State == dead) || (_State == beforedead2))
		return;
	
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == transform) || (obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == reborn))
			return;

		switch(this->GetCollisionDirection(this->GetReSizeRect(), obj->GetRect()))
		{
		case Top:
			_State = beforedead;
			break;
		}
	}
	
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == transform) || (obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == reborn))
			return;

		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
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
			//set next form
			//player mat mau
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
			// set next form
			//player mat mau
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
			// set next form
			//player mat mau
			break;
		}
	}
}

CRECT fungi::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height);
}

CRECT fungi::GetReSizeRect()
{
	return CRECT(_x - 3, _y, _x + _curSprite->_texture->Width + 6, _y + _curSprite->_texture->Height);
}

void fungi::UpdateRealTimeCollision(int time,vector<MyObject*>* listcollision)
{
	if(_State == dead)
		return;

	_listCollisionData.clear();

	// neu roi wa khoi map
	if(_y >= 800)
		_State = dead;
	if(_State != beforedead)
	{
		_nextx = _x + _vx * time;
		_nexty = _y + _vy * time;
	}
	else
	{
		_nextx = _x;
		_nexty = _y;
	}
	
	int size1 = listcollision->size();

	if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
	{
		for(int k = 0 ; k < size1; ++k)
		{
			if(listcollision->at(k) == this)
				continue;

			if((listcollision->at(k)->_ID == EObject::FUNGI) || (listcollision->at(k)->_ID == EObject::MARIO) || (listcollision->at(k)->_ID == EObject::TURTLE) || (listcollision->at(k)->_ID == EObject::BRICKBREAK))
				this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
		}
	}

	bool check = _listCollisionData.check();

	if(check == true) // co va cham
	{
		bool backPosition = false;
		int a = _listCollisionData._listNewData.size();
		for(int m = 0; m < _listCollisionData._listNewData.size(); m++)
		{
			int index = _listCollisionData._listNewData.at(m)->_indexObject;
			int idobject = _listCollisionData._listNewData.at(m)->_ID;
			EDirect dir = _listCollisionData._listNewData.at(m)->_dirCollision;
			State stateObject = listcollision->at(index)->_State;

			if(backPosition == false)
			{
				if(((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE)) && ((dir == Left) || (dir == Right)))
				{
					_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
					_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
					backPosition = true;
				}
			}
			if(idobject == BRICKBREAK)
			{
				if(stateObject == breaking || stateObject == State::Move)
				{
					_State = beforedead2;
					_vy = -0.85f;
				}
			}
			if(idobject == EObject::MARIO)
			{
				if((stateObject == transform) || (stateObject == dead) || (stateObject == beforedead) || (stateObject == reborn))
					continue;

				if((dir == Left) || (dir == Right) || (dir == Bottom))
				{
					listcollision->at(index)->_State = transform;
					if(GL_CurForm != 0)
						GL_NextForm = GL_CurForm - 1;
					if(GL_CurForm == 0)
					{
						listcollision->at(index)->_vy = -2.0;
						listcollision->at(index)->_State = beforedead;
						//break;
					}
				}
				//set next form
				//player mat mau
			}

			if((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE))
			{
				if(_State == beforedead2)
					continue;
				if(listcollision->at(index)->_State == State::attack)
					continue;

				if(dir == Left)
				{
					//_x = listcollision->at(index)->_x + TILE + 1;
					_turnLeft = false;
					listcollision->at(index)->_turnLeft = true;
				}

				if(dir == Right)
				{
					//_x = listcollision->at(index)->_x - this->_curSprite->_texture->Width - 1;
					_turnLeft = true;
					listcollision->at(index)->_turnLeft = false;
				}
			}

			//debug vs release
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		}
	} 

	_vy += GRAVITY * time;
	CheckTitleCollision(_vx,_vy,_nextx,_nexty,GL_Width,GL_Height,_curSprite->_texture->Width,_curSprite->_texture->Height);
	_x = _nextx;
	_y = _nexty;

	if(_State == beforedead)
	{
		_curSprite->SelectIndex(2);
		_timeTransform += time;
		if(_timeTransform >= 150)
			_State = dead;
		return;
	}

	if(_State != beforedead2)
	{
		if(_turnLeft == true)
			_vx = -0.1;
		else _vx = 0.1;
	}

	_curSprite->Update(time);
}



void fungi::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if((_State == beforedead2) || (_State == beforedead) || (_State == dead))
	{
		_nextY = _nextY;
		_nextX = _nextX;
		//_x = _nextX;
		//_y = _nextY;
		return;
	}

	if (_vx > 0)
	{
		bool iColTerX1 = false;
		for (int i = (_x + _width)/TILE ; i <  (_nextX + _width)/TILE; i++)
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
						_State = stand;
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