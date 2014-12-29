#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "Surface.h"
#include "ResourceManager.h"
#include "MenuSence.h"
#include "PlaySence.h"
#include "IntroSence.h"
#include "SoundManager.h"
#include "Writer.h"

MarioGame::MarioGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate):
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//TODO: Init game
	isShowInfor = false;
}

MarioGame::~MarioGame()
{
	//TODO: Release game
	if(_listSence.empty())
		_listSence.clear();
}

void MarioGame::LoadResources()
{
	SoundManager::GetInst();

	IntroSence* mn = new IntroSence(this, 4000);
	this->AddSence(mn);
}

//render before
void MarioGame::RenderFrame(int t)
{
	//TODO: UPDATE-------------------------------------------------------
	//GameObject->Update(t);
}

//render after
void MarioGame::RenderFrameAfter(int t)
{
	if(isShowInfor)
	{
		GLSpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
		float scale = 0.55f;

		char text[100];

		//title
		Writer::RenderFont2("Game info\t:...\n", 0, 560, scale);

		//current time
		time_t t = time(0);   // get time now
		struct tm* now = localtime(&t);
		sprintf(text, "Time\t\t\t\t: %d/%d/%d - %2.0d:%2.0d:%2.0d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
		Writer::RenderFont2(text, 0, 540, scale);

		//fps
		sprintf(text, "Fps\t\t\t\t\t: %f\n", this->GetFPS());
		Writer::RenderFont2(text, 0, 520, scale);

		//list sence size
		sprintf(text, "Sences\t\t: %d\n", this->_listSence.size());
		Writer::RenderFont2(text, 0, 500, scale);

		//effect
		if(GL_HasEffectSound)
			Writer::RenderFont2("Effect\t\t: TRUE", 0, 480, scale);
		else
			Writer::RenderFont2("Effect\t\t: FALSE", 0, 480, scale);

		//background
		if(GL_HasBGSound)
			Writer::RenderFont2("BgSound\t: TRUE", 0, 460, scale);
		else
			Writer::RenderFont2("BgSound\t: FALSE", 0, 460, scale);

		//current map
		sprintf(text, "Map\t\t\t\t\t: %d\n", MapLoader::_mapNumber);
		Writer::RenderFont2(text, 0, 440, scale);

		GLSpriteHandler->End();
	}
}

void MarioGame::ProcessInput(int t)
{
	//State
	//Nhan phim va giu
	
}

void MarioGame::OnKeyDown(int keyCode)
{
	//Buffer
	//Nhấn 1 lần
	//cheat game //////////////////////////////////////////////////////////////////////////////////////////////////
	if(this->IsKeyDown(DIK_LCONTROL))
	{
		switch(keyCode)
		{
			//delete savedgame file
		case DIK_DELETE:
			{
				if( remove( "saved/savedgame.txt" ) != 0 )
					GLMessage("Can not delete savedgame.txt!");
				else
					GLMessage("Delete savedgame.txt! successfull");
			}			
			break;

			//effect sound
		case DIK_S:
			{
				GL_HasEffectSound = !GL_HasEffectSound;
				if(GL_HasEffectSound == false)
				{
					SoundManager::GetInst()->StopAllEffSound();
				}
				SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			}
			break;

			//background sound
		case DIK_B:
			{
				GL_HasBGSound = !GL_HasBGSound;
				if(GL_HasBGSound == false)
				{
					SoundManager::GetInst()->StopAllBgSound();
				}else
				{
					SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU);
				}
				SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			}
			break;

			//show about us
		case DIK_A:
			GLMessage("Mario Ozawa\nDirectX 9.0\nJan-2012\n\nGameUIT Club\nDeveloper:\nJundat - TieuNun\nEmail: longpham.uit@gmail.com - ziczac_zodiac@yahoo.com");
			break;

			//show game infor
		case DIK_I:
			isShowInfor = !isShowInfor;
			break;

			//show help, show cheat guide
		case DIK_F1:
			GLMessage("All game:\
					\nLEFT CTRL + \
					\nB\t: Toogle background sound.\nS\t: Toogle effect sound.\nI\t: Toogle show game infor.\nA\t: Show about us.\nDELETE\t: Delete saved game.\n\
					\nPlay sence:\
					\nLEFT CTRL + (to increase)\
					\nLEFT CTRL + LEFT SHIFT + (to decrease)\nT\t: Time for level.\nG\t: Mario gold.\nL\t: Mario life.\nX\t: Mario experience.\
					\nQ\t: Mario transform to Large.\nW\t: Mario transform to Fire.\nE\t: Mario transform to Small.\nNum1\t: Count map number you want to go to.\nEnd\t: Go to the map number you have counted by Num1 key.");
			break;

		}
	}
}

void MarioGame::OnKeyUp(int KeyCode)
{
	//Buffer
	//Nhấn 1 lần
}