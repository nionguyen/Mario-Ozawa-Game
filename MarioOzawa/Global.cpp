
#include "Global.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//GLOBAL CONSTANT
//

// tieu nun
int GL_CurForm;

// tieu nun
int GL_NextForm;

bool		GL_IsInitedDX;
int			GL_GameDepth;
char*		GL_GameName;
int			GL_FrameRate;
int			GL_ColorMode;
bool		GL_IsFullScreen;
D3DFORMAT	GL_BackBufferFormat;

bool		GL_HasBGSound = true;
bool		GL_HasEffectSound = true;

int			GL_MapW;
int			GL_MapH;

int			GL_MapTileW;
int			GL_MapTileH;

RECT		GL_WndSize;
int			GL_Width;
int			GL_Height;

//
//GLOBAL VARIANT
//

HINSTANCE					GL_HINSTANCE;		// Handle of the game instance
HWND						GL_HWND;			// Handle of the Game Window

D3DPRESENT_PARAMETERS		GLPresentPara;
LPDIRECT3D9					GLDirect;
LPDIRECT3DDEVICE9			GLDevice;
LPDIRECT3DSURFACE9			GLBackBuffer;

LPDIRECTINPUT8				GLDirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8		GLKeyBoard;			// The keyboard device 
LPD3DXSPRITE				GLSpriteHandler;	// spriteHandler to draw texture


void GLTrace(char* format, ...)
{	
	char *_traceFile = "D:\\Trace Mario Ozawa Game.log";
	int _traceNum = 1;

	if (!_traceNum) return;

	FILE *f = stderr;
	if (_traceFile!=NULL)
	{
		if (fopen_s(&f, _traceFile,"a")!=0) 
		{
			fprintf(stderr,"WARNING: Failed to open trace file '%s' for writing!\n", _traceFile);
			return;
		}
	}
	va_list ap;
	va_start(ap, format);
	fprintf(f, format, ap);
	va_end(ap);
	fprintf(f,"\n");
	if (_traceFile != NULL) fclose(f);
}

void GLMessage(char* text)
{
	MessageBox(GL_HWND, text, "Mario Voice", MB_OK);
}

void GLTitle(char* text){
	SetWindowText(GL_HWND, text);
}