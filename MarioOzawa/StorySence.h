#pragma once

#include "gamesence.h"


class StorySence :
	public GameSence
{
public:
	DWORD _startTime;
	DWORD _allTime;
	bool _stopUpdate;

	StorySence(Game* game, int timeAni);
	~StorySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

