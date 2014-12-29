#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "Texture.h"

//Tạo 1 animation
class Sprite {
public: 
	TEXTURE* _texture;

	//start index
	int _start;

	//end index
	int _end;

	int _index;			// Current sprite index

	//time to increase index
	int _timeAni;

	int _timeLocal;

	D3DXCOLOR _color;

	Sprite::Sprite(){}
	Sprite::Sprite(TEXTURE* texture, int timeAnimation);
	Sprite::Sprite(TEXTURE* texture, int start, int end, int timeAnimation);

	//increase index
	void Next();

	//reset index
	void Reset();

	//set a particular index
	void SelectIndex(int index);

	//update animation
	void Update(int time);

	// Render current sprite at location (X,Y) at the target surface
	void Render(int x, int y, float depth = 0.5f);
	
	//Render with scale (-1, 1)
	void RenderScaleX(int x, int y, float depth = 0.5f);

	// tieu nun
	//render with scale (1, -1)
	void RenderScaleY(int x, int y, float depth = 0.5f);

	// tieu nun
	//Render Rect of texture at (x,y)
	void RenderRect(int x, int y, RECT Rect, float depth = 0.5f);

	//Render with details
	void RenderTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth = 0.5f);
	~Sprite();
};



#endif