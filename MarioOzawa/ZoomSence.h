#pragma once

#include "gamesence.h"

class ZoomSence :
	public GameSence
{
public:
	ISence* _lastSence;
	ISence* _nextSence;
	Sprite* _sprZoom;

	ZoomSence(Game* game, int timeAni, ISence* lastSence, ISence* nextSence);
	~ZoomSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};


