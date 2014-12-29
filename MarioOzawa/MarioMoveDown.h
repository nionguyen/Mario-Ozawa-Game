#pragma once
#include "Sprite.h"
#include "ResourceManager.h"

#define HIGH_MARIO_MOVE_DOWN 150
#define DEPTH_MARIO_MOVE_DOWN 0.6f
#define VY_MARIO_MOVE_DOWN 0.1f

//Effect dùng cho lúc mario đi xuống ống nước
class MarioMoveDown
{
public:
	bool IsVisiable;
	bool IsTurnLeft;
	Sprite* CurrentSprite;
	//Sprite* Flying;
	int Posx;
	int Posy;
	float deltaMove;

	MarioMoveDown(bool isTurnLeft, Sprite* marioSprite, int posx, int posy)
	{
		this->IsVisiable = true;
		this->IsTurnLeft = isTurnLeft;
		this->CurrentSprite = marioSprite;
		this->Posx = posx;
		this->Posy = posy;
		this->deltaMove = 0;

		//
		//Flying = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgFlying.png"), 50);
	}

	void Update(int time)
	{
		if(IsVisiable)
		{
			//Flying->Update(time);
			
			deltaMove += (float)time * (float)VY_MARIO_MOVE_DOWN;

			//check if complete move
			if(deltaMove >= HIGH_MARIO_MOVE_DOWN)
			{
				IsVisiable = false;
			}
		}
	}

	void Render()
	{
		if(IsVisiable)
		{
			//Flying->Render(Posx - 70, -370, DEPTH_MARIO_MOVE_DOWN);

			if(!IsTurnLeft)
				CurrentSprite->Render(Posx, (int)((float)Posy + (float)deltaMove), DEPTH_MARIO_MOVE_DOWN);
			else
				CurrentSprite->RenderScaleX(Posx, (int)((float)Posy + (float)deltaMove), DEPTH_MARIO_MOVE_DOWN);
		}		
	}

};

