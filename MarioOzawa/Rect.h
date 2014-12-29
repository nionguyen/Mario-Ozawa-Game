#pragma once

#include <d3d9.h>

//Thay thế cho struct RECT, bởi vì xét va chạm bằng RECT viết rất nhiều hàm phức tạp
//Bổ sung thêm các hàm cần thiết khác
class CRECT
{
public:
	float Left, Top, Right, Bottom;
	
	CRECT(void);
	CRECT(RECT rect);
	CRECT(float _left, float _top, float _right, float _bottom);
	~CRECT(void);
	RECT ToRECT();

	//Kiểm tra va chạm với 1 CRECT khác
	bool IsCollision (CRECT _Rect);

	void SetX(float x);
	void SetY(float y);
	void Move(float x, float y);
};

