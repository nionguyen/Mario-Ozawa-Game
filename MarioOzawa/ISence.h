
#pragma once

//Interface contact between "Game" class and "GameSence" class
class ISence
{
public:
	//public virtual method for class "Game" call
	virtual void UpdateRender(int t) = 0;
	virtual void ProcessInput() = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
	virtual void Load() = 0;

	virtual bool IsDead() = 0;
};

