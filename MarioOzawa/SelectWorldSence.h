#pragma once

#include "gamesence.h"
#include "Mario.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "MarioMoveDown.h"

#define TIME_TO_DELETE_SAVE_GAME 1500 //~3second

class SelectWorldSence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	MapLoader*	_MapLoader;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Mario*	_mario;
	MarioMoveDown* _effectMoveDown;
	bool _isExitting;
	bool _isShowMessage;
	bool _isKeyDowning;
	int _countTime;
	Sprite* _sprNode;

	SelectWorldSence(Game* game, int timeAni);
	~SelectWorldSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

