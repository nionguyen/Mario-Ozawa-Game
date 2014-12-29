#include "PlaySence.h"
#include "MenuSence.h"
#include "ZoomSence.h"
#include "MapLoader.h"
#include "Writer.h"
#include "SoundManager.h"
#include "LoseGameSence.h"

PlaySence::PlaySence(Game* game, int timeAni)
	: GameSence(game, timeAni)
{
	SoundManager::GetInst()->PlayBgSound(SOUND_B_GAME1);
	_isExitting = false;
	IsVisiable = true;
}

PlaySence::~PlaySence(void)
{
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_Camera != NULL)
	{
		delete _Camera;
		_Camera = NULL;
	}

	if(_mario != NULL)
	{
		delete _mario;
		_mario = NULL;
	}

	if(_BackgroundMng != NULL)
	{
		delete _BackgroundMng;
		_BackgroundMng = NULL;
	}
}

void PlaySence::_Load()
{
	//reset time
	_timeForLevel = TIME_FOR_LEVEL;

	_mario = new Mario(50, 50);
	_BackgroundMng = new BackgroundManager();
	
	//
	//savedgame.txt trong thư mục saved chứa thông tin sau:
	//+ map thứ mấy(tên file map, vd: "map0.png", rồi MapLoader sẽ vào thư mục map mà kiếm và load background của map đó lên
	//+ trạng thái của map đó, bao gồm:
	//tên obj:
	//x
	//y
	//(gồm cả mario)
	//nếu chưa có file savedgame hoặc savedgame không chứa gì
	//khi đó sẽ load map đầu tiên như bình thường
	MapLoader::LoadSavedGameFormFile(GL_FILE_SAVE_GAME);
	
	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);
	_QuadTree = new QuadTree(mapRECT);

	MapLoader::TranslateMap(_QuadTree, _BackgroundMng, _mario, _timeForLevel);
	_BackgroundMng->Translate();
	_Camera = new Camera(CRECT(GL_WndSize));

	//change sence
	IsVisiable = false;
	_game->AddSence(new ChangeMapSence(_game, &IsVisiable, MapLoader::_mapNumber, 100));
}

// nhan 1 lan
void PlaySence::_OnKeyDown(int keyCode)
{
	static int countMapToGo = 0;

	//cheat game /////////////////////////////////////////////////////////////////////////////////////////////////
	//control + key => increase
	//control + shift + key => decrease 
	if(_game->IsKeyDown(DIK_LCONTROL))
	{
		switch (keyCode)
		{
		case DIK_Q:
			_mario->TransformMario(1, 0);
			break;

		case DIK_W:
			_mario->TransformMario(1, 2);
			break;

		case DIK_E:
			_mario->TransformMario(2, 1);
			break;

		case DIK_L:
			if(_game->IsKeyDown(DIK_LSHIFT))
				_mario->life--;
			else
				_mario->life++;
			break;

		case DIK_G:
			if(_game->IsKeyDown(DIK_LSHIFT))
				_mario->gold--;
			else
				_mario->gold++;
			break;

		case DIK_T:
			if(_game->IsKeyDown(DIK_LSHIFT))
				_timeForLevel -= 5000;
			else
				_timeForLevel += 5000;
			break;

		case DIK_X:
			if(_game->IsKeyDown(DIK_LSHIFT))
				_mario->exp -= 50;
			else
				_mario->exp += 50;
			break;

		case DIK_1:
			countMapToGo++;
			break;

		case DIK_END:
			{
				if(countMapToGo >= 1)
				{
					_mario->_vx = 0;
					MapLoader::_mapNumber = countMapToGo - 1;

					LoadNewMap();

					//change sence
					IsVisiable = false;
					_game->AddSence(new ChangeMapSence(_game, &IsVisiable, MapLoader::_mapNumber, 100));
					countMapToGo = 0;
				}
			}
			break;
		}
	}
	else // control game ////////////////////////////////////////////////////////////////////////////////////////////
		switch(keyCode){
		case DIK_ESCAPE:
			{
				if(! (_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP))
				if(! _isExitting)
				{
					//save game
					if(_mario->life >= 0 && _mario->_State != dead) // save game
					{
						MapLoader::SaveGameToFile(_QuadTree, _mario, _timeForLevel, GL_FILE_SAVE_GAME);
					}
					else // delete file save
					{
						MapLoader::DeleteSavedGame(GL_FILE_SAVE_GAME);
					}

					_isExitting = true;

					//got to menu
					MenuSence* mn = new MenuSence(_game, 0);
					ZoomSence* zs = new ZoomSence(_game, 500, this, mn);
					_game->AddSence(zs);

					SoundManager::GetInst()->StopBgSound(SOUND_B_GAME1);
					SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU, true, true);
				}			
			}
			break;

		case DIK_SPACE:
			if(! (_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP))
			{
				_mario->Jump();
			}
			break;

		case DIK_Z:
			_mario->Fire();
			break;

		case DIK_UP:
			if(! (_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP))
			{
				_mario->Jump();
			}
			break;
		}
}

//nhan 1 lan
void PlaySence::_OnKeyUp(int keyCode)
{
	
}

// nhan va giu
void PlaySence::_ProcessInput()
{
	if (_game->IsKeyDown(DIK_RIGHT))
	{
		//if(_mario->_State != jumping)
		{
			_mario->TurnRight();
		}
	}
	else if (_game->IsKeyDown(DIK_LEFT))
	{
		if(! (_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP))
		{
			//if(_mario->_State != jumping)
			{
				_mario->TurnLeft();
			}
		}
	}
	else if(_game->IsKeyDown(DIK_DOWN))
	{ 
		if(! (_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP))
			_mario->ShitDown();
	}
	else
	{
		_mario->Stand();
	}
}

void PlaySence::_UpdateRender(int time)
{
	if(! IsVisiable)
		return;

#pragma region Begin Render
	D3DXMATRIX mat;
	float x = _Camera->GetRect().Left;
	float y = _Camera->GetRect().Top;
	D3DXVECTOR2 trans(- x, - y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, 0.0f, &trans);
	GLSpriteHandler->SetTransform(&mat);
	GLSpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
#pragma endregion
	//------------------------------------------------------------------------
	
	//update time
	if(_timeForLevel > 0)
	{
		_timeForLevel -= time;

		//check time out
		if(_timeForLevel < 0)
		{
			//sound
			SoundManager::GetInst()->PlayEffSound(SOUND_E_DEATH_SHOT, false);

			_timeForLevel = 0;
			_mario->RunBeforeDie();
			_timeForLevel = TIME_FOR_LEVEL + 3 * 500;
		}
	}
	
	_Camera->Update(_mario);
	RECT r = GL_WndSize;
	r.top = GL_Height - _alpha * GL_Height;


	//khi lose game, thì _mapNumber đc reset lại = 0, do đó sẽ vẽ sai
	if(MapLoader::_mapNumber == 2)
		ResourceMng::GetInst()->GetSurface("image/imgBgGame2.png")->Render(NULL, &r);
	else
		ResourceMng::GetInst()->GetSurface("image/imgBgGame.png")->Render(NULL, &r);

	_BackgroundMng->UpdateRender(_Camera->GetCameraExpand(), time);
	
	//_mario->Update(time);

	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _mario, time);
	
	_mario->Render();
	
	//check fail game
	if(_mario->life <= 0 && _mario->_State == dead && 
		!_isExitting)
	{
		//////////////////////////////////////////////////////////////////////////
		//fix lỗi camera còn di chuyển sau khi game over
		_mario->_vx = 0;
		_Camera->_vx = 0;
		//////////////////////////////////////////////////////////////////////////

		GL_CurForm = 0;
		GL_NextForm = 0;

		MapLoader::DeleteSavedGame(GL_FILE_SAVE_GAME);

		_isExitting = true;

		SoundManager::GetInst()->StopBgSound(SOUND_B_GAME1);

		LoseGameSence* screen = new LoseGameSence(_game, 1000, this);

		_game->AddSence(screen);
	}

	//------------------------------------------------------------------------
#pragma region End Render
	D3DXMATRIX matDefaut;
	D3DXMatrixTransformation2D(&matDefaut, NULL, 0.0f, NULL, NULL, 0.0f, NULL); 
	GLSpriteHandler->SetTransform(&matDefaut);
	
	//draw life and gold  and info
	char text[100];
	
	//life
	sprintf(text, "life x %d", _mario->life);
	Writer::RenderFont2(text, 0, 5, 0.75f);

	//exp
	sprintf(text, "exp x %d", _mario->exp);
	Writer::RenderFont2(text, 6, 35, 0.75f);

	//gold
	Sprite* sprCoin = new Sprite(ResourceMng::GetInst()->GetTexture("image/Coin.png"), -1);
	sprCoin->RenderTransform(220, 5, D3DXVECTOR2(0.8f, 0.8f), 0);
	sprintf(text, " x %d", _mario->gold);
	Writer::RenderFont2(text, 220, 5, 0.75f);

	//map
	sprintf(text, "map x %d", MapLoader::_mapNumber);
	Writer::RenderFont2(text, 400-20, 5, 0.75f);

	//time
	sprintf(text, "time x %d", _timeForLevel / 500);
	Writer::RenderFont2(text, 600-20, 5, 0.75f);
	
	GLSpriteHandler->End();
#pragma endregion

	//mario complete map, go ahead
	if(_mario->_x >= GL_MapW - MARIO_DELTA_X_COMPLETE_MAP)
	{
		_mario->TurnRight();
		_mario->_vx = MARIO_VX_COMPLETE_MAP;
	}

	//check complete map pppppppppppppppppppppppppppppppppppppppppppppppppppppp
	if(_mario->GetRect().Right >= GL_MapW)
	{
		//sound win game
		//SoundManager::GetInst()->PlayEffSound(SOUND_E_WIN, false);

		//stop mario
		_mario->_vx = 0;

		//save game
		MapLoader::SaveGameToFile(_QuadTree, _mario, _timeForLevel, GL_FILE_SAVE_GAME);

		LoadNewMap();

		//change sence
		IsVisiable = false;
		_game->AddSence(new ChangeMapSence(_game, &IsVisiable, MapLoader::_mapNumber, 100));
		return;
	}
}

void PlaySence::LoadNewMap(void)
{
	//reset time
	_timeForLevel = TIME_FOR_LEVEL;

	//delete resource
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_BackgroundMng != NULL)
	{
		delete _BackgroundMng;
		_BackgroundMng = NULL;
	}

	if(_Camera != NULL)
	{
		delete _Camera;
		_Camera = NULL;
	}

	//Load new game
	MapLoader::LoadMapFormFile(MapLoader::_mapNumber + 1, true, true, true, true);

	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);
	_QuadTree = new QuadTree(mapRECT);
	_BackgroundMng = new BackgroundManager();
	_Camera = new Camera(CRECT(GL_WndSize));

	MapLoader::TranslateMap(_QuadTree, _BackgroundMng, _mario, _timeForLevel);
	_BackgroundMng->Translate();
}

