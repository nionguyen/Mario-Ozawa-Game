
#ifndef _MARIO_GAME_H_
#define _MARIO_GAME_H_

#include <d3dx9.h>

#include "Global.h"
#include "Game.h"
#include "Sprite.h"
#include "Mario.h"

//Main Game, implement class "Game"
class MarioGame: public Game
{
public:
	MarioGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate);
	~MarioGame();
		
protected:
	//check whether show game infor in top up
	bool isShowInfor;

	virtual void RenderFrame(int Delta);

	//render top up all object in game
	virtual void RenderFrameAfter(int Delta);
	virtual void LoadResources();

	//handle input
	virtual void ProcessInput(int Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


#endif