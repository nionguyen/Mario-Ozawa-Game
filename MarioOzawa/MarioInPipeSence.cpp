
#include "MarioInPipeSence.h"
#include "MenuSence.h"
#include "PlaySence.h"
#include "MapLoader.h"
#include "Writer.h"
#include "SoundManager.h"
#include "ZoomSence.h"


MarioInPipeSence::MarioInPipeSence(Game* game, bool* isVisible, int timeAni)
	: GameSence(game, timeAni)
{
	//no play sound
	this->IsVisiable = isVisible;
	IsExitting = false;
}

MarioInPipeSence::~MarioInPipeSence(void)
{
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_MapLoader != NULL)
	{
		delete _MapLoader;
		_MapLoader = NULL;
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

void MarioInPipeSence::_Load()
{
	_mario = new Mario(1, 400);
	
	_MapLoader = new MapLoader();
	_MapLoader->LoadMapFormFile(-1, true, true, true, true);

	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);

	_QuadTree = new QuadTree(mapRECT);
	_BackgroundMng = new BackgroundManager();
	int tempNoNeed = 0;
	_MapLoader->TranslateMap(_QuadTree, _BackgroundMng, _mario, tempNoNeed);
	_BackgroundMng->Translate();
	_Camera = new Camera(CRECT(GL_WndSize));

	_mario->_x = 1;
	_mario->_y = 400;
}

// nhan 1 lan
void MarioInPipeSence::_OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_ESCAPE:
		{
			_state = TransOff;
			MenuSence* mn = new MenuSence(_game, 100);
			_game->AddSence(mn);
		}
		break;
	}
}

//nhan 1 lan
void MarioInPipeSence::_OnKeyUp(int keyCode)
{

}

// nhan va giu
void MarioInPipeSence::_ProcessInput()
{
}

void MarioInPipeSence::_UpdateRender(int time)
{
#pragma region Begin Render
	//translate camera
	D3DXMATRIX mat;
	float x = _Camera->GetRect().Left;
	float y = _Camera->GetRect().Top;
	D3DXVECTOR2 trans(- x, - y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, 0.0f, &trans);
	GLSpriteHandler->SetTransform(&mat);
	GLSpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
#pragma endregion

	//------------------------------------------------------------------------
	_Camera->Update(_mario);

	RECT r = GL_WndSize;
	r.top = GL_Height - _alpha * GL_Height;

	ResourceMng::GetInst()->GetSurface("image/imgBgGame.png")->Render(NULL, &r);
	_BackgroundMng->UpdateRender(_Camera->GetCameraExpand(), time);
	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _mario, time);
	
	_mario->TurnRight();

	{//do not run out of the map
		//right
		if(_mario->GetRect().Right >= GL_MapW && IsExitting == false)
		{
			IsExitting = true;
			//change map here
			//////////////////////////////////////////////////////////////////////////
			SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			_state = Off;
			*this->IsVisiable = true;
			MapLoader::_mapNumber = 2;
			MapLoader::LoadMapFormFile(2, true, true, true, true);
		}

		//left
		if(_mario->_x <= 0)
		{
			_mario->_x = 0;
		}
	}

	if(_mario->_x < 500)
	{
		_mario->Render();
	}

	//------------------------------------------------------------------------
#pragma region End Render
	//translate camera back
	D3DXMATRIX matDefaut;
	D3DXMatrixTransformation2D(&matDefaut, NULL, 0.0f, NULL, NULL, 0.0f, NULL); 
	GLSpriteHandler->SetTransform(&matDefaut);
	//

	//end Render
	GLSpriteHandler->End();
#pragma endregion
}

