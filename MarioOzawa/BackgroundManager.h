#pragma once

#include "Rect.h"
#include "Sprite.h"

//Quản lý các đối tượng
// + Ko di chuyển
// + Ko xét va chạm
// + Có animation
class BackgroundManager
{
public:
	//Kích thước của toàn bộ map, tính theo TILE(50px*50px)
	int _mapW;
	int _mapH;

	// mảng 2 chiều lưu id của các obj là background
	// chỉ dùng cho việc vẽ
	int **_board;
	//board[i][j]   ^
	// i: 0-> mapH  |
	// j: 0-> mapW --->

	//mảng 2 chiều, lưu con trỏ của các sprite
	//dùng để vẽ các background động
	Sprite*** _boardSprite;

	//Load các resource, khởi tạo các sprite cần thiết, đặt vào đúng vị trí trong _boardSprite
	void Translate();
	void UpdateRender(CRECT camera, int time);
	~BackgroundManager(void);

	BackgroundManager(void);
};

