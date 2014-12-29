#pragma once

#include "gamesence.h"

#define COUNT_OPTION 4

class OptionSence :
	public GameSence
{
public:
	static int _curSelect;
	Sprite* _sprMarioHead;

	OptionSence(Game* game, int timeAni);
	~OptionSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

