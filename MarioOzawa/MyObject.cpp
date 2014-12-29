#include "MyObject.h"
#include "Global.h"
#include "ResourceManager.h"
#include <math.h>
#include "TileMap.h"
#include "Writer.h"
MyObject::MyObject(float xx, float yy)
{
	_x = xx;
	_y = yy;
	_State = State::alive;
	_turnLeft = true;
}


MyObject::~MyObject(void)
{

}

CRECT MyObject::GetRect()
{
	return CRECT(_x, _y, _x + TILE, _y + TILE);
}

bool MyObject::CanCollide(){
	return true;
}

bool MyObject::IsAlive(){
	return (_State != dead);
}

void MyObject::Update(int time)
{
}

void MyObject::Render()
{

}

void MyObject::CheckCollision(MyObject* obj)
{
	
}

EDirect MyObject::GetCollisionDirection(CRECT r1, CRECT r2)
{
	if (r1.IsCollision(r2))
	{
		float top = abs(r1.Top - r2.Bottom);
		float botom = abs(r1.Bottom - r2.Top);
		float left = abs(r1.Left - r2.Right);
		float right = abs(r1.Right - r2.Left);
		
		float minRL = right < left ? right : left;
		float minTB = top < botom ? top : botom;
		float rs = minRL < minTB ? minRL : minTB;

		if (rs == top)
		{
			return EDirect::Top;
		}
		if (rs == botom)
		{
			return EDirect::Bottom;
		}
		if (rs == left)
		{
			return EDirect::Left;
		}
		if (rs == right)
		{
			return EDirect::Right;
		}
	}

	return EDirect::None;
}

void MyObject::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{

}

void MyObject::RealTimeCollision(CRECT r1, CRECT r2)
{
	float x0, y0, x1, y1, X, Y;
	bool _left2right = true;
	bool _up2down = true;

	bool _collision = false;

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
		X = r2.Left;
	}
	else // right -> left
	{
		_left2right = false;
		x0 = r1.Left;
		X = r2.Right;
	}

	if(_vy > 0) // top -> down
	{
		_up2down = true;
		y0 = r1.Bottom;
		Y = r2.Top;
	}
	else // down -> top
	{
		_up2down = false;
		y0 = r1.Top;
		Y = r2.Bottom;
	}
	x1 = _x + _vx; // next position after moving
	y1 = _y + _vy; // next position after moving


	// xet ngang

	float giaodiemX, giaodiemX2, giaodiemY, giaodiemY2;
	giaodiemY = (_vy / _vx) * (X - x0) + y0;
	giaodiemX = X;
	if(_vy > 0)
		giaodiemY2 = giaodiemY - (r1.Bottom - r1.Top);
	else giaodiemY2 = giaodiemY + (r1.Bottom - r1.Top);

	if ((r2.Top <= giaodiemY) && (giaodiemY <= r2.Bottom))
	{
		if (_left2right == true)
		{
			if ((x0 <= giaodiemX) && (giaodiemX <= x1))
				// diem o tren cua ball
			{
				int a = 0;
				a++;
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
		else
		{
			if ((x0 >= giaodiemX) && (giaodiemX >= x1))
				// diem o tren cua ball
			{
				int a = 0;
				a++;
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
		if ((r2.Top <= giaodiemY2) && (giaodiemY2 <= r2.Bottom))
		{
			if (_left2right == true)
			{
				if ((x0 <= giaodiemX) && (giaodiemX <= x1))
					// diem o tren cua ball
				{
					int a = 0;
					a++;
					// va cham right
					_collision = true;
					_dirCollision = EDirect::Right;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY2);
				}
			}
			else
			{
				if ((x0 >= giaodiemX) && (giaodiemX >= x1))
					// diem o tren cua ball
				{
					int a = 0;
					a++;
					// va cham left
					_collision = true;
					_dirCollision = EDirect::Left;
					delta = GetDistance(x0,y0,giaodiemX,giaodiemY2);
				}
			}
		}
	}

	if (_left2right == true)
	{
		if ((x0 <= giaodiemX) && (giaodiemX <= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < r2.Top) && (giaodiemY2 > r2.Bottom))
			{
				int a = 0;
				a++;
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		if ((x0 >= giaodiemX) && (giaodiemX >= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < r2.Top) && (giaodiemY2 > r2.Bottom))
			{
				int a = 0;
				a++;
				// va cham left
				_collision = true;
				_dirCollision = EDirect::Left;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	{
		if (_vx > 0)
			deltaX = (x1 - giaodiemX) + (r1.Right - r1.Left);
		if (_vx < 0)
			deltaX = (x1 - giaodiemX);

	}


	// xet doc

	giaodiemX = x0 + (_vx / _vy) * (Y - y0);
	giaodiemY = Y;
	if(_vx > 0)
		giaodiemX2 = giaodiemX - (r1.Right - r1.Left);
	else
		giaodiemX2 = giaodiemX + (r1.Right - r1.Left);
	if ((r2.Left <= giaodiemX) && (giaodiemX <= r2.Right))
	{
		if (_up2down == true)
		{
			if ((giaodiemY >= y0) && (giaodiemY <= y1))
			{
				int a = 0;
				a++;
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
		else
		{
			if ((giaodiemY <= y0) && (giaodiemY >= y1))
			{
				int a = 0;
				a++;
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		if ((r2.Left <= giaodiemX2) && (giaodiemX2 <= r2.Right))
		{
			if (_up2down == true)
			{
				if ((giaodiemY >= y0) && (giaodiemY <= y1))
				{
					int a = 0;
					a++;
					// va cham down
					_collision = true;
					_dirCollision = EDirect::Bottom;
					delta = GetDistance(x0,y0,giaodiemX2,giaodiemY);
				}
			}
			else
			{
				if ((giaodiemY <= y0) && (giaodiemY >= y1))
				{
					int a = 0;
					a++;
					// va cham top
					_collision = true;
					_dirCollision = EDirect::Top;
					delta = GetDistance(x0,y0,giaodiemX2,giaodiemY);
				}
			}
		}
	}

	if (_up2down == true)
	{
		if ((giaodiemY >= y0) && (giaodiemY <= y1))
		{
			if ((giaodiemX < r2.Left) && (giaodiemX2 > r2.Right))
			{
				int a = 0;
				a++;
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		if ((giaodiemY <= y0) && (giaodiemY >= y1))
		{
			if ((giaodiemX < r2.Left) && (giaodiemX2 > r2.Right))
			{
				int a = 0;
				a++;
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = GetDistance(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	//if (_collision == true)
	{

		if (_vy > 0)
			deltaY = (y1 - giaodiemY) + (r1.Bottom - r1.Top);
		if (_vy < 0)
			deltaY = (y1 - giaodiemY);
	}
	if (_collision == true)
	{
		_x -= (deltaX );
		_y -= (deltaY );
	}

	// luu IDobject : de xu li logic,state neu co va cham
	// luu deltaX,deltaY : de xu li cap nhat position
	// _dirCollision : luu huong va cham : uu tien top,bottom -> xu li logic,state neu co va cham theo huong
	// luu delta : de chon object nao va cham
	// index cua object trong ListObject
	// toan bo luu vo 1 list
	// cuoi cung lay list nay ra xet lai. chon nhung object thuc su va cham roi xu li
}

float MyObject::GetDistance(float x0,float y0,float x1,float y1)
{
	float t1,t2;
	t1 = pow(x0 - x1,2);
	t2 = pow(y0 - y1,2);
	return sqrt(t1+t2);
}

void MyObject::RealTimeCollision1(CRECT r1, MyObject *obj,int indexObject,int time)
{

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
		X = obj->GetRect().Left;
	}

	else // right -> left
	{
		_left2right = false;
		x0 = r1.Left;
		X = obj->GetRect().Right;
	}

	if(_vy > 0) // top -> down
	{
		_up2down = true;
		y0 = r1.Bottom;
		Y = obj->GetRect().Top;
	}
	else // down -> top
	{
		_up2down = false;
		y0 = r1.Top;
		Y = obj->GetRect().Bottom;
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

	if ((obj->GetRect().Top <= giaodiemY) && (giaodiemY <= obj->GetRect().Bottom))
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
		if ((obj->GetRect().Top <= giaodiemY2) && (giaodiemY2 <= obj->GetRect().Bottom))
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
			if ((giaodiemY < obj->GetRect().Top) && (giaodiemY2 > obj->GetRect().Bottom))
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
			if ((giaodiemY < obj->GetRect().Top) && (giaodiemY2 > obj->GetRect().Bottom))
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
	if ((obj->GetRect().Left <= giaodiemX) && (giaodiemX <= obj->GetRect().Right))
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
		if ((obj->GetRect().Left <= giaodiemX2) && (giaodiemX2 <= obj->GetRect().Right))
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
			if ((giaodiemX < obj->GetRect().Left) && (giaodiemX2 > obj->GetRect().Right))
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
			if ((giaodiemX < obj->GetRect().Left) && (giaodiemX2 > obj->GetRect().Right))
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
		_listCollisionData.add(new CollisionData(obj->_ID,_dirCollision,deltaX,deltaY,delta,indexObject));
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

void MyObject::UpdateRealTimeCollision(int Time,vector<MyObject*>*listcollision)
{

}