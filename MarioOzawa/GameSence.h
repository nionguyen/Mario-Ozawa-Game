

#ifndef __GAMESENCE_H__
#define __GAMESENCE_H__

#include "Game.h"
#include "ISence.h"
#include "ResourceManager.h"

//State of a sence
enum SenceState{
	TransOn = 0,	//begin transform
	On = 1,			//on view
	TransOff = 2,	//begin transform to shutdown
	Off = 3,		//shutdowned
};

//Implement inteface ISence
//Manage a show in a TV channel
class GameSence : public ISence
{
public:
	//the game manage it
	//this sence belong to _game
	Game*			_game;
	SenceState		_state;

	//alpha channel (color) of all sence, used for transforming
	float			_alpha;

	//time for transform when begin and end
	//in state TransOn and TransOff
	float			_timeAni;

	GameSence(Game* game, int timeAni);
	virtual ~GameSence(void);

	//implement in ISnece
	//Used for calling from outside
	void UpdateRender(int t);
	void ProcessInput();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void Load();
	bool IsDead();

protected:
	//Will be implement in sub class
	//contained in above function
	virtual void _UpdateRender(int i);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
	//
};


#endif __GAMESENCE_H__