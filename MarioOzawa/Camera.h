
#pragma once

#include "Rect.h"
#include "MyObject.h"

#define DELTA_CAMERA_X		10
#define DELTA_CAMERA_Y		100
#define EXPAND_CAMERA		100

#include <d3dx9.h>

//Quản lý vị trí của cảnh hiện tại trong game, so với Map
class Camera
{
protected:
public:
	//đúng bằng kích thước màn hình
	CRECT _rectCamera;		//bound //800x600

	//vận tốc di chuyển của camera
	//giúp cho camera di chuyển theo mario mượt hơn
	float _vx;				//velocity 
	float _vy;

	Camera(CRECT rect);
	~Camera(void);

	//update vị trí mới, dựa vào vị trí player
	void Update(MyObject* player);
	
	//trả về kích thước camera (màn hình)
	CRECT GetRect()
	{
		return _rectCamera;
	}

	//trả về kích thước mở rộng camera, dùng cho việc xét va chạm
	CRECT GetCameraExpand();
};

