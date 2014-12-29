#ifndef __TEXTURE_H__
#define __TEXTURE_H__


#include <d3d9.h>
#include <d3dx9.h>

#include "Global.h"


//Lớp bao chứa 1 LPDIRECT3DTEXTURE9
//Quản lý các thông tin khác của LPDIRECT3DTEXTURE9 đó
class TEXTURE{
public:
	char* FileName;
	RECT Size;
	LPDIRECT3DTEXTURE9 Texture;

	//Luôn giả sử 1 texture sẽ dùng cho 1 sprite
	int Cols;
	int Rows;

	//Số tile có trong đó, có thể Count # Cols * Rows, đôi khi lại = nhau
	int Count;

	int Width; //width of 1 frame
	int Height; //height of 1 frame

	TEXTURE(char* _fileName, int cols, int rows, int count){
		Cols = cols;
		Rows = rows;
		Count = count;
		FileName = _fileName;
		this->Load();
	}

	~TEXTURE(){
		if(this->Texture != NULL){
			this->Texture->Release();
		}
	}

	void Load(){
		D3DXIMAGE_INFO info; 
		HRESULT result;

		result = D3DXGetImageInfoFromFile(FileName, &info);
		
		RECT s = {0, 0, info.Width, info.Height};
		this->Size = s;

		Width = info.Width / Cols;
		Height = info.Height / Rows;

		if (result != D3D_OK)
		{
			GLMessage("Can not load texture");
			GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
			OutputDebugString(FileName);
			return;
		}

		result = D3DXCreateTextureFromFileEx(
			GLDevice,
			FileName,
			info.Width,
			info.Height,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT ,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0, //color
			&info,
			NULL,
			&Texture
		);

		if (result != D3D_OK) 
		{
			GLMessage("Can not load texture");
			GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);
			return;
		}
	}

	void Render(int x, int y, float depth = 0.5f){
		D3DXVECTOR3 position((float)x, (float)y, depth);

		GLSpriteHandler->Draw(
			Texture,
			&Size,
			NULL,
			&position,
			D3DCOLOR_ARGB(255, 255, 255, 255)
			);
	}
};


#endif