#pragma once
#ifndef __GAME_H__
#define __GAME_H__


#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include <vector>
using namespace std;

#include "Global.h"
#include "ISence.h"

//Quản lý toàn bộ game
//Init game
//Input
//Sence
//Game loop
//...
class Game
{
protected:
	BYTE					_KeyStates[256];						// DirectInput keyboard state array

	DIDEVICEOBJECTDATA		_KeyEvents[ GL_KEY_BUFFER_SIZE ];		// Buffered keyboard data
		
	DWORD					_DeltaTime;			// Time between the last frame and current frame
	
	//------
	vector<ISence*>			_listSence;

	//--------------------------- Init Function ------------------------------------
	void _SetScreenDimension(int Mode);

	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();

	//-------------------------- Run Function ---------------------------------------

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// Render a single frame
	// call Game::RenderFrame
	void _RenderFrame();

	void _ProcessKeyBoard();
	void _ProcessInput();
	void _LoadResources();
	

	// Place holder for sub classes
	
	virtual void RenderFrame(int Delta);
	virtual void RenderFrameAfter(int Delta);
	virtual void LoadResources();
	virtual void ProcessInput(int Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	

public:
	LPDIRECT3D9 GetDirectX();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();

	int GetMode();

	int GetScreenWidth();
	int GetScreenHeight();
	int GetDepth();
	float GetFPS();

	int IsKeyDown(int KeyCode);
	//
	void AddSence(ISence* sence);

	Game(HINSTANCE hInstance, char* Name, int Mode, int IsFullscreen, int FrameRate);
	virtual ~Game();

	void Release();

	// Initialize the game with set parameters
	// InitWindows
	// InitDX
	// InitKeyboard
	// LoadResource
	void Init();

	// Run game
	void Run();
};



#endif __GAME_H__