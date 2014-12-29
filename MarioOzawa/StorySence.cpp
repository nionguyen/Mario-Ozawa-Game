#include "StorySence.h"
#include "MenuSence.h"
#include "SoundManager.h"

StorySence::StorySence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	_allTime = 3000;
	_startTime = GetTickCount();
	_stopUpdate = false;
}

StorySence::~StorySence(void)
{
}

void StorySence::_Load()
{
}

// nhan 1 lan
void StorySence::_OnKeyDown(int keyCode){
}

void StorySence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void StorySence::_ProcessInput()
{
}

void StorySence::_UpdateRender(int t)
{
	//update
	//begin to load out
	if(GetTickCount() - _startTime >= _allTime)
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
	}

	//render
	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * _alpha), 255, 255, 255);
	D3DCOLOR finalColor = color;

	GLDevice->ColorFill(GLBackBuffer, NULL, D3DCOLOR_XRGB(50, 50, 50));
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	GLSpriteHandler->Draw(ResourceMng::GetInst()->GetTexture("image/imgLogo.png")->Texture, NULL, NULL, &D3DXVECTOR3(100 + 150, 201, 0), finalColor);

	GLSpriteHandler->End();
}

