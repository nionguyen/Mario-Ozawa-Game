#pragma once

#include "gamesence.h"
#define MAX_LEVEL 6


class ChangeMapSence :
	public GameSence
{
public:
	Sprite* mario;
	bool* IsVisiable;

	int count;

	int CurrentLevel;
	int StationX[MAX_LEVEL];
	int StationY[MAX_LEVEL];

	ChangeMapSence(Game* game, bool* isVisible, int curlevel, int timeAni);
	~ChangeMapSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();

	void DrawLines(int x, int y, int nx, int xy);
};


