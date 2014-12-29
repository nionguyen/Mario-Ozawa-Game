#pragma once

#include "ResourceManager.h"
#include "Global.h"

//Quản lý việc viết chữ trong game
class Writer
{
public:
	//Viết bằng font 1
	//text: chữ cần viết
	//x, y: vị trí viết
	//scale: tỉ lệ co giãn
	static void RenderFont1(char* text, int x, int y, float scale = 1.0);

	//Viết bằng font 2
	//text: chữ cần viết
	//x, y: vị trí viết
	//scale: tỉ lệ co giãn
	static void RenderFont2(char* text, int x, int y, float scale = 1.0);
};

