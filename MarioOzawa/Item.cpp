#include "Item.h"
#include "ResourceManager.h"
#include "TileMap.h"
#include "SoundManager.h"
#include "Mario.h"
Item::Item(float x, float y, EBrickItemKind kindOfItem): MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/brick.png"), 0);
	_ID = EObject::ITEM;
	_item = kindOfItem;
	_x = x;
	_y = y;
	oriY = _y;
	_vx = 0.0f;
	_vy = 0.0f;
	_State = stand;

	if(_item == EBrickItemKind::FLOWER)
	{
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Flower.png"), 400);
		//_turnLeft = true;
	}
	if(_item == EBrickItemKind::LARGER)
	{
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Lager.png"), 0);
		_curSprite->SelectIndex(0);
		_turnLeft = false;
	}

	if(_item == EBrickItemKind::SHOOTER)
	{
		_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Lager.png"), 0);
		_curSprite->SelectIndex(1);
		_turnLeft = false;
	}
}

Item::~Item(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void Item::Update(int time)
{
	return;
	if(_State == dead)
		return;
	if(_State == stand)
	{
		_y-= 0.1*time;
		if(_y <= (oriY - 50))
		{
			_y = oriY - 50;
			_State = Move;
		}
	}
	if(_State == Move)
	{
		if((_item == EBrickItemKind::LARGER) || (_item == EBrickItemKind::SHOOTER))
		{
			_nextx = _x + _vx * time ;
			_nexty = _y + _vy * time;

			_vy += GRAVITY * time;
			CheckTitleCollision(_vx,_vy,_nextx,_nexty,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height);
			_x = _nextx;
			_y = _nexty;
			if(_turnLeft == true)
				_vx = - 0.2;
			else _vx = 0.2;
		}
	}
	if(_item == EBrickItemKind::FLOWER)
		_curSprite->Update(time);
}

void Item::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	if(_State == dead)
		return;
	_listCollisionData.clear();

	if(_State == stand)
	{
		_y-= 0.1*time;
		if(_y <= (oriY - 44))
		{
			_y = oriY - 44.0f;
			_State = Move;
		}
	}
	if(_State == Move)
	{
		if((_item == EBrickItemKind::LARGER) || (_item == EBrickItemKind::SHOOTER))
		{
			_nextx = _x + _vx * time ;
			_nexty = _y + _vy * time;

			int size1 = listcollision->size();

			if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
			{
				for(int k = 0 ; k < size1; ++k)
				{
					if(listcollision->at(k) == this)
						continue;
					if((listcollision->at(k)->_ID == EObject::MARIO) || (listcollision->at(k)->_ID == EObject::BRICKBREAK))
						this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
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
					/*
					//if(backPosition == false)
					{
						if((idobject == BRICKBREAK) && (stateObject == Move))
						{
							// newwwwwwwwwwwwwwww
							_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
							_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
							_vy = - 10.0f;
							_turnLeft = !_turnLeft;
							backPosition = true;
						}
					}
					*/
					if(idobject == EObject::BRICKBREAK)
					{
						if((dir != Top) && (stateObject == Move) && (this->_item != FLOWER))
						{
							if(_vy >= 0.0f)
								_vy = -1.2f;
							_y = listcollision->at(index)->_y - _curSprite->_texture->Height;//((brickItem*)listcollision->at(index))->_item->_curSprite->_texture->Height;
						}
					}
					if(idobject == EObject::MARIO)
					{
						if((stateObject == transform) || (stateObject == dead) || (stateObject == beforedead) || (stateObject == reborn))
							continue;
						_State = dead;
						if(this->_item != SHOOTER)
						{
							if(GL_CurForm != 2)
							{
								listcollision->at(index)->_State = transform;
								GL_NextForm = GL_CurForm + 1;
								if((GL_CurForm == 0) && (GL_NextForm == 1))
									listcollision->at(index)->_y -= 50;
							}
						}// player transform or + heart khi nhat dc item here
						else
						{
							((Mario*)listcollision->at(index))->life++;
						}
					}
				}
			}
			_vy += GRAVITY * time;
			CheckTitleCollision(_vx,_vy,_nextx,_nexty,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height);
			_x = _nextx;
			_y = _nexty;
			if(_turnLeft == true)
				_vx = - 0.2;
			else _vx = 0.2;

		}
	}
	if(_item == EBrickItemKind::FLOWER)
		_curSprite->Update(time);
}


void Item::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x, (int)_y);
}

void Item::CheckTitleCollision(
	float &_vx, float &_vy, 
	float &_nextX, float &_nextY, 
	float _maxWidth, float _maxHeight, 
	int _width,int _height)
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

CRECT Item::GetRect()
{
	//return CRECT(_x + 10, _y, _x + _curSprite->_texture->Width - 20, _y + _curSprite->_texture->Height);
	return CRECT(_x, _y, _x + _curSprite->_texture->Width, _y + _curSprite->_texture->Height);
}

void Item::CheckCollision(MyObject* obj)
{
	if((_State == dead) || (_State == beforedead))
		return;
	
	if(obj->_ID == EObject::MARIO)
	{
		
		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != None)
		{
			_State = dead;
			if(this->_item != SHOOTER)
			{
				if(GL_CurForm != 2)
				{
					obj->_State = transform;
					GL_NextForm = GL_CurForm + 1;
					if((GL_CurForm == 0) && (GL_NextForm == 1))
						obj->_y -= 50;
				}	
			}// player transform or + heart khi nhat dc item here
			else
			{
				//((Mario*)listcollision->at(index))->life++;
				((Mario*)obj)->life++;
			}
		}
	}
	if(obj->_ID == BRICKBREAK)
	{
		if((this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != Top) && (this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != None))
		{
			if(obj->_State == Move)
			{
				
				_y = obj->_y - _curSprite->_texture->Height;
			}
		}
	}
}