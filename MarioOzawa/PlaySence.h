#pragma once

#include "gamesence.h"
#include "Mario.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "ChangeMapSence.h"

//time to complete a leve 5min
#define TIME_FOR_LEVEL (150000) 

//sence of the battle and blood
class PlaySence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Mario*	_mario;

	//check if this sence is visiable
	bool IsVisiable;

	//check if is extiing
	bool _isExitting;
	
	//time for 1 level, count down from TIME_FOR_LEVEL to zero
	int _timeForLevel; 
	
	PlaySence(Game* game, int timeAni);
	~PlaySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();

	void LoadNewMap(void);
};

