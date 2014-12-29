
#include "BrickBreak.h"
#include "ResourceManager.h"
#include "Global.h"
#include "SoundManager.h"
#include "TileMap.h"

brickBreak::brickBreak(float x, float y,State state)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Brick_Break.png"), 500);
	_ID = EObject::BRICKBREAK;
	if(state == State::start)
		_State = stand;
	else _State = state;
	up = true;
	_yOri = y;
	_nextx = 0.0f;
	_nexty = 0.0f;
	_vx = 0.0f;
	_vy = 0.0f;
	_rectBreak1.left = 0;
	_rectBreak1.top = 0;
	_rectBreak1.right = _rectBreak1.left + TILE/2;
	_rectBreak1.bottom = _rectBreak1.top + TILE/2;

	_rectBreak2.left = TILE/2;
	_rectBreak2.top = 0;
	_rectBreak2.right = _rectBreak2.left + TILE/2;
	_rectBreak2.bottom = _rectBreak2.top + TILE/2;

	_rectBreak3.left = 0;
	_rectBreak3.top = TILE/2;
	_rectBreak3.right = _rectBreak3.left + TILE/2;
	_rectBreak3.bottom = _rectBreak3.top + TILE/2;

	_rectBreak4.left = TILE/2;
	_rectBreak4.top = TILE/2;
	_rectBreak4.right = _rectBreak4.left + TILE/2;
	_rectBreak4.bottom = _rectBreak4.top + TILE/2;

	_xBreak1 = _x;
	_yBreak1 = _y;

	_xBreak2 = _x + TILE/2;
	_yBreak2 = _y;

	_xBreak3 = _x;
	_yBreak3 = _y + TILE/2;

	_xBreak4 = _x + TILE/2;
	_yBreak4 = _y + TILE/2;

}


brickBreak::~brickBreak(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void brickBreak::Update(int time)
{
	return;
	if(_State == breaking)
	{
		if((_x - _xBreak1) < 50)
		//	_State = dead;
		{
			_xBreak1 -= 0.7*time;
			_xBreak2 += 0.7*time;
			_xBreak3 -= 0.7*time;
			_xBreak4 += 0.7*time;

			_yBreak1 -= 0.8*time;
			_yBreak2 -= 0.8*time;
			_yBreak3 -= 0.4*time;
			_yBreak4 -= 0.4*time;
		}
		else
		{
			_xBreak1 -= 0.4*time;
			_xBreak2 += 0.4*time;
			_xBreak3 -= 0.4*time;
			_xBreak4 += 0.4*time;

			_yBreak1 += 0.5*time;
			_yBreak2 += 0.5*time;
			_yBreak3 += 1.0*time;
			_yBreak4 += 1.0*time;
		}
		if((_x - _xBreak1) > 100)
		{
			_State = dead;
			TileMap::GetInst()->RemoveTileAt(_x,_y);
		}
	}
	if(_State == Move)
	{
		if(up == true)
		{
			_nexty -= 0.22f * time;
			if(_nexty <= (_yOri - 25))
			{
				_nexty = _yOri - 25;
				up = false;
			}
		}
		if(up == false)
		{
			_nexty+= 0.22f * time;
			if(_nexty >= _yOri)
			{
				_nexty = _yOri;
				up = true;
				_State = stand;
			}
		}
		_y = _nexty;
	}
	//_curSprite->Update(time);
}

void brickBreak::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	_listCollisionData.clear();

	if(_State == breaking)
	{
		if((_x - _xBreak1) < 50)
			//	_State = dead;
		{
			_xBreak1 -= 0.7*time;
			_xBreak2 += 0.7*time;
			_xBreak3 -= 0.7*time;
			_xBreak4 += 0.7*time;

			_yBreak1 -= 0.8*time;
			_yBreak2 -= 0.8*time;
			_yBreak3 -= 0.4*time;
			_yBreak4 -= 0.4*time;
		}
		else
		{
			_xBreak1 -= 0.4*time;
			_xBreak2 += 0.4*time;
			_xBreak3 -= 0.4*time;
			_xBreak4 += 0.4*time;

			_yBreak1 += 0.5*time;
			_yBreak2 += 0.5*time;
			_yBreak3 += 1.0*time;
			_yBreak4 += 1.0*time;
		}
		if((_x - _xBreak1) > 100)
		{
			_State = dead;
			TileMap::GetInst()->RemoveTileAt(_x,_y);
		}
	}

	if(_State == Move)
	{
		if(up == true)
		{
			_nexty = _y - (0.22f * time);
			if(_nexty <= (_yOri - 25))
			{
				_nexty = (_yOri - 25);
				up = false;
			}
		}

		if(up == false)
		{
			_nexty = _y + (0.22f * time);
			if(_nexty >= _yOri)
			{
				_nexty = _yOri;
				up = true;
				_State = stand;
			}
		}

		int size1 = listcollision->size();

		if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
		{
			for(int k = 0 ; k < size1; ++k)
			{
				if(listcollision->at(k) == this)
					continue;

				if((listcollision->at(k)->_ID == EObject::FUNGI) || (listcollision->at(k)->_ID == EObject::TURTLE))
				{
					this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
				}

				if((listcollision->at(k)->_ID == EObject::BRICKITEM) && (listcollision->at(k)->_State != hasItem))
				{
					this->RealTimeCollisionWithItem(this->GetRect(),(brickItem*)listcollision->at(k),k,time);
				}
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

				//debug vs release
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				if((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE))
				{
					//if(dir == Top)
					{
						listcollision->at(index)->_vy = -0.85f;
						listcollision->at(index)->_State = beforedead2;
					}
				}

				if(idobject == EObject::ITEM)
				{
					if((dir != Bottom) && (_State == Move) && (((brickItem*)listcollision->at(index))->_item->_item != FLOWER))
					{
						if(((brickItem*)listcollision->at(index))->_item->_vy >= 0.0f)
							((brickItem*)listcollision->at(index))->_item->_vy = -1.2f;
						((brickItem*)listcollision->at(index))->_item->_y = _y - ((brickItem*)listcollision->at(index))->_item->_curSprite->_texture->Height;
						//((brickItem*)listcollision->at(index))->_item->_turnLeft = !((brickItem*)listcollision->at(index))->_item->_turnLeft;
					}
				}
			}
		}

		_y = _nexty;
	}
	//_curSprite->Update(time);
}


void brickBreak::Render()
{
	if((_State == stand) || (_State == Move))
		_curSprite->Render((int)_x, (int)_y);
	if(_State == breaking)
	{
		_curSprite->RenderRect((int)_xBreak1,(int)_yBreak1,_rectBreak1);
		_curSprite->RenderRect((int)_xBreak2,(int)_yBreak2,_rectBreak2);
		_curSprite->RenderRect((int)_xBreak3,(int)_yBreak3,_rectBreak3);
		_curSprite->RenderRect((int)_xBreak4,(int)_yBreak4,_rectBreak4);
	}
}
CRECT brickBreak::GetRect()
{
	return CRECT(_x , _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height );
	//return CRECT(_x + 13, _y, _x + _curSprite->_texture->Width - 26, _y + _curSprite->_texture->Height );
}
void brickBreak::CheckCollision(MyObject* obj)
{
	if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
		return;
	if((obj->_ID == EObject::TURTLE) || (obj->_ID == EObject::FUNGI))
	{
		if((_State == Move) || (_State == breaking))
		{
			obj->_State = beforedead2;
			obj->_vy = -0.85f;
		}
	}
	/*
	if(_State != stand)
		return;

	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == beforedead) || (obj->_State == dead))
			return;

		if(GL_CurForm == 0)
			return;
		EDirect dir = this->GetCollisionDirection(this->GetRect(), obj->GetRect());

		switch(dir)
		{
		case Bottom:
			if(_State == stand)
			{
				_State = breaking;
				SoundManager::GetInst()->PlayEffSound(SOUND_E_BROKEN);
			}
			break;
		case Top:
			break;

		case Left:
			break;

		case Right:
			break;
			
		case None:
			break;
		}
	} */

}


void brickBreak::RealTimeCollisionWithItem(CRECT r1, brickItem *obj,int indexObject,int time)
{
	if(obj->_State == hasItem)
		return;
	if(obj->_item->_State == dead)
		return;
	float x0, y0, x1, y1, X, Y;
	bool _left2right = true;
	bool _up2down = true;
	
	bool _collision = false;
	bool _rightleft = false;
	// khoang cach lui ve theo truc x, va truc y
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	// khoang cach tu diem xuat phat den giao diem
	float delta = 0.0f; // xet chon object va cham
	EDirect _dirCollision = EDirect::None;

	if(_vx > 0) // left -> right
	{
		_left2right = true;
		x0 = r1.Right;
		X = obj->_item->GetRect().Left;
	}
	else // right -> left
	{
		_left2right = false;
		x0 = r1.Left;
		X = obj->_item->GetRect().Right;
	}

	if(_vy > 0) // top -> down
	{
		_up2down = true;
		y0 = r1.Bottom;
		Y = obj->_item->GetRect().Top;
	}
	else // down -> top
	{
		_up2down = false;
		y0 = r1.Top;
		Y = obj->_item->GetRect().Bottom;
	}
	//x1 = _x + _vx; // next position after moving
	//y1 = _y + _vy; // next position after moving
	//if(_vx > 0 )
		x1 = x0 + (_nextx - _x);
	//else x1 = x0 - (_nextx - _x);
	//if(_vy > 0 )
		y1 = y0 + (_nexty - _y);
	//else y1 = y0 - (_nexty - _y);

	// xet ngang

	float giaodiemX, giaodiemX2, giaodiemY, giaodiemY2;
	giaodiemY = (_vy / _vx) * (X - x0) + y0;
	giaodiemX = X;
	if(_vy > 0)
		giaodiemY2 = giaodiemY - (r1.Bottom - r1.Top);
	else giaodiemY2 = giaodiemY + (r1.Bottom - r1.Top);

	if ((obj->_item->GetRect().Top <= giaodiemY) && (giaodiemY <= obj->_item->GetRect().Bottom))
	{
		if (_left2right == true)
		{
			//x1 = _nextx + (r1.Right - r1.Left);
			if ((x0 <= giaodiemX) && (giaodiemX <= x1))
				// diem o tren cua ball
			{
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
			//x1 = _nextx;
		}
		else
		{
			if ((x0 >= giaodiemX) && (giaodiemX >= x1))
				// diem o tren cua ball
			{
				// va cham left
				_collision = true;
				_dirCollision = EDirect::Left;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		// diem o duoi
		//xet giao diem 2, cach giaodiemY 1 doan = chieu cao cua ball
		//giaodiemY += 100.0f;
		if ((obj->_item->GetRect().Top <= giaodiemY2) && (giaodiemY2 <= obj->_item->GetRect().Bottom))
		{
			if (_left2right == true)
			{
				//x1 = _nextx + (r1.Right - r1.Left);
				if ((x0 <= giaodiemX) && (giaodiemX <= x1))
					// diem o tren cua ball
				{
					// va cham right
					_collision = true;
					_dirCollision = EDirect::Right;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
				}
				//x1 = _nextx;
			}
			else
			{
				if ((x0 >= giaodiemX) && (giaodiemX >= x1))
					// diem o tren cua ball
				{
					// va cham left
					_collision = true;
					_dirCollision = EDirect::Left;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
				}
			}
		}
	}

	if (_left2right == true)
	{
		//x1 = _nextx + (r1.Right - r1.Left);
		if ((x0 <= giaodiemX) && (giaodiemX <= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < obj->_item->GetRect().Top) && (giaodiemY2 > obj->_item->GetRect().Bottom))
			{
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
		//x1 = _nextx;
	}
	else
	{
		if ((x0 >= giaodiemX) && (giaodiemX >= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < obj->_item->GetRect().Top) && (giaodiemY2 > obj->_item->GetRect().Bottom))
			{
				// va cham left
				_collision = true;
				_dirCollision = EDirect::Left;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	/*
	{
		if (_vx > 0)
			deltaX = (x1 - giaodiemX); //+ (r1.Right - r1.Left);
		if (_vx < 0)
			deltaX = (x1 - giaodiemX) - (r1.Right - r1.Left);
		if(_vx == 0)
			deltaX = 0.0f;

	}
	*/
	if(_collision == true)
	{
		deltaX = (x1 - giaodiemX);
		_rightleft = true;
	}
	
	// xet doc

	giaodiemX = x0 + (_vx / _vy) * (Y - y0);
	giaodiemY = Y;
	if(_vx > 0)
		giaodiemX2 = giaodiemX - (r1.Right - r1.Left);
	else
		giaodiemX2 = giaodiemX + (r1.Right - r1.Left);
	if ((obj->_item->GetRect().Left <= giaodiemX) && (giaodiemX <= obj->_item->GetRect().Right))
	{
		if (_up2down == true)
		{
			//y1 = _nexty + (r1.Bottom - r1.Top);
			if ((giaodiemY >= y0) && (giaodiemY <= y1))
			{
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);

			}
			//y1 = _nexty;
		}
		else
		{
			if ((giaodiemY <= y0) && (giaodiemY >= y1))
			{
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		if ((obj->_item->GetRect().Left <= giaodiemX2) && (giaodiemX2 <= obj->_item->GetRect().Right))
		{
			if (_up2down == true)
			{
				//y1 = _nexty + (r1.Bottom - r1.Top);
				if ((giaodiemY >= y0) && (giaodiemY <= y1))
				{
					// va cham down
					_collision = true;
					_dirCollision = EDirect::Bottom;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
				}
				//y1 = _nexty;
			}
			else
			{
				if ((giaodiemY <= y0) && (giaodiemY >= y1))
				{
					// va cham top
					_collision = true;
					_dirCollision = EDirect::Top;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
				}
			}
		}
	}

	if (_up2down == true)
	{
		//y1 = _nexty + (r1.Bottom - r1.Top);
		if ((giaodiemY >= y0) && (giaodiemY <= y1))
		{
			if ((giaodiemX < obj->_item->GetRect().Left) && (giaodiemX2 > obj->_item->GetRect().Right))
			{
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
		//y1 = _nexty;
	}
	else
	{
		if ((giaodiemY <= y0) && (giaodiemY >= y1))
		{
			if ((giaodiemX < obj->_item->GetRect().Left) && (giaodiemX2 > obj->_item->GetRect().Right))
			{
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	//if (_collision == true)
// 	{
// 
// 		if (_vy > 0)
// 			deltaY = (y1 - giaodiemY); //+ (r1.Bottom - r1.Top);
// 		if (_vy < 0)
// 			deltaY = (y1 - giaodiemY);
// 		if(_vy == 0)
// 			deltaY = 0.0f;
// 	}
	//if((_vy > 0.0f ) && (_vx == 0.0f))
		if((_vy != 0.0f ) && (_vx == 0))
			deltaY = (y1 - giaodiemY);
	//if((_vy < 0.0f ) && (_vx == 0.0f))
		//deltaY = (y1 - giaodiemY);
		//if(_vy != 0.0f)
			//deltaX = (x1 - giaodiemX);
		//if(_vy == 0.0f)
		//	deltaY = 0.0f;
//		if(_vx == 0.0f)
	//		deltaX = 0.0f;
		if(_collision == true)
		{
			if((_vx != 0.0f) && (_vy != 0.0f))
			{
				deltaY = (y1 - giaodiemY);

				if(_rightleft == false)
				{
					if((_vy >= (0.01*(time - 1))) && (_vy <= (0.01*(time + 1))))
					{

					}
					else
					{
						if(_vx > 0.0f)
							deltaX = x1 - giaodiemX;
						if(_vx < 0.0f)
							deltaX = -(x1 - giaodiemX);
					}
				}
			}
			if(_vy == 0.0f)
				deltaY = 0.0f;
			/*if(_vx > 0)
				deltaX +=1;
			if(_vx < 0)
				deltaX -=1;
			if(_vy > 0)
				deltaY +=1;
			if(_vx < 0)
				deltaY -=1;*/
			if(_dirCollision == Right)
				deltaY = 0.0f;
			if(_dirCollision == Left)
				deltaY = 0.0f;
			if(_vx == 0.0f)
				deltaX = 0.0f;
			//deltaX = (x1 - giaodiemX2);
			//deltaX = (x1 - X);
		}


	if (_collision == true)
	{
		//CollisionData
		if(_dirCollision == Right)
			int v =0;
		if(_dirCollision == Left)
			int d=0;
		_listCollisionData.add(new CollisionData(EObject::ITEM,_dirCollision,deltaX,deltaY,delta,indexObject));
		//_nextx -= (deltaX );
		//_nexty -= (deltaY );
		//_nexty += 1;
		//_vy = 0;
	}

	// luu IDobject : de xu li logic,state neu co va cham
	// luu deltaX,deltaY : de xu li cap nhat position
	// _dirCollision : luu huong va cham : uu tien top,bottom -> xu li logic,state neu co va cham theo huong
	// luu delta : de chon object nao va cham
	// index cua object trong ListObject
	// toan bo luu vo 1 list
	// cuoi cung lay list nay ra xet lai. chon nhung object thuc su va cham roi xu li
}