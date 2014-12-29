#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <d3d9.h>
#include "Global.h"

//Lớp bao chứa 1 LPDIRECT3DSURFACE9
//Quản lý các thông tin khác của LPDIRECT3DSURFACE9 đó
class SURFACE{
public:
	char* FileName;
	RECT Size;
	LPDIRECT3DSURFACE9 Surface;

	SURFACE(char* _fileName){
		FileName = _fileName;
		this->Load();
	}

	~SURFACE(){
		if(this->Surface != NULL){
			this->Surface->Release();
		}
	}

	void Render(const RECT* sRect, const RECT* dRect){
		GLDevice->StretchRect(
			this->Surface,		// from 
			sRect,				// which portion?
			GLBackBuffer,		// to 
			dRect,				// which portion?
			D3DTEXF_NONE);
	}

	void Render(int x, int y){
		RECT dr = {x, y, Size.right + x, Size.bottom + y};

		GLDevice->StretchRect(
			this->Surface,		// from 
			&this->Size,				// which portion?
			GLBackBuffer,		// to 
			&dr,				// which portion?
			D3DTEXF_NONE);
	}

	void Load()
	{
		D3DXIMAGE_INFO info;

		HRESULT result = D3DXGetImageInfoFromFile(FileName, &info);
		if (result != D3D_OK)
		{
			GLMessage("Can not load surface");
			GLTrace("[ERROR] Failed to get image info '%s'", FileName);
			return;
		}

		this->Size.top = 0;
		this->Size.left = 0;
		this->Size.bottom = info.Height;
		this->Size.right = info.Width;

		GLDevice->CreateOffscreenPlainSurface(
			info.Width,				// width
			info.Height,			// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT ,		
			&Surface,
			NULL);

		result = D3DXLoadSurfaceFromFile(
			Surface, 		// surface
			NULL,			// destination palette	
			NULL,			// destination rectangle 
			FileName,			
			NULL,			// source rectangle
			D3DX_DEFAULT, 	// filter image
			0,				// transparency (0 = none) //color
			NULL);			// reserved

		if (result != D3D_OK)
		{
			GLMessage("Can not load surface");
			GLTrace("[ERROR] D3DXLoadSurfaceFromFile() failed");
			return;
		}
	}
};




#endif