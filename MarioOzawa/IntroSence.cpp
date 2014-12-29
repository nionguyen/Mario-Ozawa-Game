#include "IntroSence.h"
#include "MenuSence.h"
#include "SoundManager.h"

IntroSence::IntroSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	_timeAni = 1000;
	_startTime = GetTickCount();
	_stopUpdate = false;
}

IntroSence::~IntroSence(void)
{
}

void IntroSence::_Load()
{
}

// nhan 1 lan
void IntroSence::_OnKeyDown(int keyCode){
}

void IntroSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void IntroSence::_ProcessInput()
{
}

void IntroSence::_UpdateRender(int t)
{
	//update
	//begin to load out
	if(GetTickCount() - _startTime >= START_TIME_INTRO)
	{
		_state = TransOff;
	}

	//add new sence before this end
	if(_state == SenceState::TransOff && _stopUpdate == false && _alpha <= 0.05)
	{
		SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU);
		_stopUpdate = true;

		MenuSence* mn = new MenuSence(_game, 100);
		_game->AddSence(mn);

		this->_state = Off;
	}

	//render
	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * _alpha), 255, 255, 255);
	D3DCOLOR finalColor = color;

	GLDevice->ColorFill(GLBackBuffer, NULL, D3DCOLOR_XRGB(50, 50, 50));
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	GLSpriteHandler->Draw(ResourceMng::GetInst()->GetTexture("image/imgLogo.png")->Texture, NULL, NULL, &D3DXVECTOR3(100 + 150, 201, 0), finalColor);
	
	GLSpriteHandler->End();
}

