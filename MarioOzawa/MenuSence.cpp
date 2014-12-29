#include "MenuSence.h"
#include "PlaySence.h"
#include "OptionSence.h"
#include "SoundManager.h"
#include "ZoomSence.h"
#include "SelectWorldSence.h"

int MenuSence::_curSelect = 0;

MenuSence::MenuSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	//_curSelect = 0;
}

MenuSence::~MenuSence(void)
{
}

void MenuSence::_Load()
{
	GLKeyBoard->Acquire();
	_sprMarioHead = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgMarioHead.png"), 1500);
}

// nhan 1 lan
void MenuSence::_OnKeyDown(int keyCode){

	// control game //////////////////////////////////////////////////////////////////////////////////////////////////
	switch(keyCode){
		case DIK_RETURN:
			if(_curSelect == 0){ //play
				//stop sound
				//SoundManager::GetInst()->StopBgSound(SOUND_B_MENU);
				//SoundManager::GetInst()->PlayEffSound(SOUND_E_PIPE);
				//goto game
				//PlaySence* pl = new PlaySence(_game, 0);
				//_state = TransOff;
				
				SelectWorldSence* pl = new SelectWorldSence(_game, 0);
				ZoomSence* zs = new ZoomSence(_game, 500, this, pl);
				_game->AddSence(pl);
				this->_state = TransOff;

			}else if(_curSelect == 1){ //option
				//do not stop sound
				SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);

				//goto option
				OptionSence* ot= new OptionSence(_game, 100);
				_game->AddSence(ot);
				_state = TransOff;

			}else if(_curSelect == 2){ //exit
				SoundManager::GetInst()->PlayEffSound(SOUND_E_DEATH);
				ZoomSence* zs = new ZoomSence(_game, 1700, this, NULL);
				_game->AddSence(zs);
			}

			break;

		case DIK_UP:
			if(_curSelect > 0){
				_curSelect--;
				SoundManager::GetInst()->PlayEffSound(SOUND_E_CLICK);
			}
			break;

		case DIK_DOWN:
			if(_curSelect < MAX_MENU - 1){
				_curSelect++;
				SoundManager::GetInst()->PlayEffSound(SOUND_E_CLICK);
			}
			break;
	}
}

void MenuSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void MenuSence::_ProcessInput()
{
}

void MenuSence::_UpdateRender(int t)
{
	//--------------------------------------------UPDATE------------------------------
	if(_sprMarioHead->_index == 1 && _sprMarioHead->_timeLocal >= _sprMarioHead->_timeAni/7)
		_sprMarioHead->SelectIndex(0);
	_sprMarioHead->Update(t);


	//--------------------------------------------RENDER------------------------------
	RECT destRect = GL_WndSize;
	destRect.top = GL_Height - _alpha * GL_Height;
	
	ResourceMng::GetInst()->GetSurface("image/imgBgMenu.png")->Render(&destRect, &destRect);

	if(true){
		GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		ResourceMng::GetInst()->GetTexture("image/imgItemPlay.png")->Render(627, 307);
		ResourceMng::GetInst()->GetTexture("image/imgItemOption.png")->Render(606, 342);
		ResourceMng::GetInst()->GetTexture("image/imgItemQuit.png")->Render(638, 378);
		switch(_curSelect)
		{
			case 0:
				_sprMarioHead->Render(545, 293);
				break;
				
			case 1:
				_sprMarioHead->Render(545, 328);
				break;

			case 2:
				_sprMarioHead->Render(545, 363);
				break;
		}
		

		GLSpriteHandler->End();
	}
}

