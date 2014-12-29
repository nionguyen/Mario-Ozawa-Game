#pragma once

#include "gamesence.h"
#include "PlaySence.h"

class LoseGameSence :
	public GameSence
{
public:
	PlaySence* _playSence;

	LoseGameSence(Game* game, int timeAni, PlaySence* playSence);
	~LoseGameSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

