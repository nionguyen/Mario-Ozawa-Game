#pragma once

#include "gamesence.h"

class CreditSence :
	public GameSence
{
public:
	CreditSence(Game* game, int timeAni);
	~CreditSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};


