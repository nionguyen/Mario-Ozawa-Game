
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//Manager all
//Global constants
//Global variants
//Global functoins

//
//GLOBAL CONSTANT
//

//size of one tile in map(brick, flower, ...)
#define TILE			50

//id in map, used for obj (hushroom, monster, tirtle, ...
#define MIN_OBJ_ID		151
#define MAX_OBJ_ID		158

//id in map, used for ground (ground is object that check collision and Render, but no animation, no move, 
#define MIN_GROUND_ID	101
#define MAX_GROUND_ID	106

//id in map, used for background (mountain, pole, pipe, tree...)
#define MIN_BG_ID		11
#define MAX_BG_ID		32

//view mode(used in contructor of game class)
#define GL_RESOLUTION_640_480_24	0
#define GL_RESOLUTION_800_600_24	1
#define GL_RESOLUTION_1024_768_24	2
//
#define GL_RESOLUTION_640_480_32	10
#define GL_RESOLUTION_800_600_32	11
#define GL_RESOLUTION_1024_768_32	12
//
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024

//file save game
#define GL_FILE_SAVE_GAME "saved/savedgame.txt"

//
//GLOBAL VARIANT
//


// tieu nun
// form hien tai, va tuong lai cua Mario
extern int GL_CurForm;
extern int GL_NextForm;

extern bool			GL_IsInitedDX;		//check if dx is inited
extern int			GL_GameDepth;		//depth in game class (i dont know
extern char*		GL_GameName;		//name of game, view in caption
extern int			GL_FrameRate;		//frame rate(30 -> 60)
extern int			GL_ColorMode;		//color mode to init dx
extern bool			GL_IsFullScreen;	//check if windows or fullscreen
extern D3DFORMAT	GL_BackBufferFormat;//backbuffer format, used in initing dx

extern bool			GL_HasBGSound;		//check if background music is on
extern bool			GL_HasEffectSound;	//check if sound effect is on

extern int			GL_MapW;			//full map width, px
extern int			GL_MapH;			//full map height, px

extern int			GL_MapTileW;			//map width in tile
extern int			GL_MapTileH;			//map height in tile

extern int			GL_Width;			//width of game screen
extern int			GL_Height;			//height of game screen
extern RECT			GL_WndSize;			//size of game screen

extern HINSTANCE					GL_HINSTANCE;		// Handle of the game instance
extern HWND							GL_HWND;			// Handle of the Game Window

extern D3DPRESENT_PARAMETERS		GLPresentPara;
extern LPDIRECT3D9					GLDirect;			//handle dx
extern LPDIRECT3DDEVICE9			GLDevice;			//dx device
extern LPDIRECT3DSURFACE9			GLBackBuffer;		//backbuffer

extern LPDIRECTINPUT8				GLDirectInput;		// The DirectInput object         
extern LPDIRECTINPUTDEVICE8			GLKeyBoard;			// The keyboard device 
extern LPD3DXSPRITE					GLSpriteHandler;	// spriteHandler to Render texture

//
//GLOBAL FUNCTION
//

//write string to a tracing file
void GLTrace(char* format, ...);

//show a message box
void GLMessage(char* text);

//show string to the caption of window
void GLTitle(char* text);

#endif