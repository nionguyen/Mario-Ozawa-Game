
#include "GameSence.h"


GameSence::GameSence(Game* game, int timeAni){
	_game = game;
	_timeAni = timeAni;
	_timeAni = _timeAni <= 0 ? 0.0001 : _timeAni;
	_alpha = 0;
	_state = SenceState::TransOn;
};

GameSence::~GameSence(){
	
};

void GameSence::Load(){
	_Load();
}

void GameSence::UpdateRender(int t){
	// UPDATE ----------------------------------- UPDATE ---------------------------
	//Update mặc định
	switch(_state){
	case SenceState::TransOn:
		_alpha += t / _timeAni;

		if(_alpha >= 1){
			_alpha = 1;
			_state = SenceState::On;
		}
		break;

	case SenceState::On:
		_alpha = 1;
		break;

	case SenceState::TransOff:
		_alpha -= t / _timeAni;

		if(_alpha <= 0){
			_alpha = 0;
			_state = SenceState::Off;
		}
		break;

	case SenceState::Off:
		_alpha = 0;
		break;
	}

	//thừa kế ở lớp con
	//if(_state != Off)
	_UpdateRender(t);
}

void GameSence::ProcessInput(){
	//if(_state == On)
		_ProcessInput();
}

void GameSence::OnKeyDown(int keyCode){
	//if(_state == On)
		_OnKeyDown(keyCode);
}

void GameSence::OnKeyUp(int keyCode){
	//if(_state == On)
		_OnKeyUp(keyCode);
}

bool GameSence::IsDead(){
	return (_state == Off);
};

//--------------- virtual function ---------------
//sẽ được thừa kế ở các lớp con
void GameSence::_UpdateRender(int i){}
void GameSence::_ProcessInput(){}
void GameSence::_OnKeyDown(int keyCode){}
void GameSence::_OnKeyUp(int keyCode){}
void GameSence::_Load(){}
//end --- //--------------- virtual function ---------------
