// File:		main.cpp
// Project:		MarioOzawa
// Create:		Pham Tan Long


#include <windows.h>
#include "MarioGame.h"
#include "Global.h"
#include "ResourceManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int bFullScreen = 0;
	
	if (MessageBox(NULL, "Would you like fullscreen?", "INFORMATION", MB_YESNO) == IDYES)
	{
		// we set a bool to true if the user wants fullscreen
		bFullScreen = 1;
	}
	else
	{
		bFullScreen = 0;
	}

	MarioGame game(hInstance,
		"Mario",
		GL_RESOLUTION_800_600_24,
		bFullScreen,
		60);

	game.Init();
	
	GLTitle("Mario Ozawa");
	
	game.Run();

	return 0;
}


