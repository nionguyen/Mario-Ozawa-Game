#include "CreditSence.h"
#include "OptionSence.h"
#include "SoundManager.h"

CreditSence::CreditSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
}


CreditSence::~CreditSence(void)
{
}


void CreditSence::_Load()
{
}

// nhan 1 lan
void CreditSence::_OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_RETURN:
		{
			SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			_state = TransOff;
			OptionSence* option = new OptionSence(_game, 100);
			_game->AddSence(option);
		}
		break;

	case DIK_UP:
		break;

	case DIK_DOWN:
		break;
	}
}

void CreditSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void CreditSence::_ProcessInput()
{
}

void CreditSence::_UpdateRender(int t)
{
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//
	RECT destRect = GL_WndSize;
	destRect.top = GL_Height - _alpha * GL_Height;

	ResourceMng::GetInst()->GetSurface("image/imgBgCredit.png")->Render(&destRect, &destRect);
	//
	GLSpriteHandler->End();
}

