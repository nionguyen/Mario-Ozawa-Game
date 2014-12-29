#include "LoseGameSence.h"
#include "MenuSence.h"
#include "SoundManager.h"
#include "Writer.h"
#include "ZoomSence.h"

LoseGameSence::LoseGameSence(Game* game, int timeAni, PlaySence* playSence)
	:GameSence(game, timeAni)
{
	this->_playSence = playSence;
}

LoseGameSence::~LoseGameSence(void)
{
}

void LoseGameSence::_Load()
{
	//SoundManager::GetInst()->PlayEffSound(SOUND_E_WIN, false);
	SoundManager::GetInst()->PlayBgSound(SOUND_B_OPTION_STATE, false);
}

// nhan 1 lan
void LoseGameSence::_OnKeyDown(int keyCode){
	if(keyCode == DIK_RETURN)
	{
		//got to menu
		MenuSence* mn = new MenuSence(_game, 0);
		ZoomSence* zs = new ZoomSence(_game, 500, this->_playSence, mn);
		_game->AddSence(zs);

		SoundManager::GetInst()->StopAllBgSound();
		SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU, true, true);

		this->_state = TransOff;
		//this->_playSence->_state = TransOff;
	}
}

void LoseGameSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void LoseGameSence::_ProcessInput()
{
}

void LoseGameSence::_UpdateRender(int t)
{
	//render
	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * _alpha), 255, 255, 255);
	D3DCOLOR finalColor = color;

	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//GLSpriteHandler->Draw(ResourceMng::GetInst()->GetTexture("image/imgLogo.png")->Texture, NULL, NULL, &D3DXVECTOR3(100 + 150, 201, 0), finalColor);
	Writer::RenderFont1("Game over!!", 200, 300, 2.0f);

	GLSpriteHandler->End();
}

