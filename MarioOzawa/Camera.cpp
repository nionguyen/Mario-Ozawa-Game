#include "Camera.h"
#include "Global.h"

Camera::Camera(CRECT rect)
{
	this->_rectCamera = rect;
	_vx = 0;
	_vy = 0;
}

Camera::~Camera(void)
{
}

void Camera::Update(MyObject* player)
{
	//Windows size
	float haftWndWidth = GL_Width/2;
	float haftWndHeight = GL_Height/2;
	
	//camera position
	float cameraX = _rectCamera.Left;
	float cameraY = _rectCamera.Top;
	
	//player position
	float playerX = player->_x;
	float playerY = player->_y;

	//---------- right
	if(playerX > cameraX + haftWndWidth + DELTA_CAMERA_X)
	{
		_vx = playerX - cameraX - haftWndWidth - DELTA_CAMERA_X;
	}

	//------------ left
	if(playerX < cameraX + haftWndWidth - DELTA_CAMERA_X)
	{
		_vx = playerX - cameraX - haftWndWidth + DELTA_CAMERA_X;
	}
	
	//------------ bottom
	if(playerY > cameraY + haftWndHeight + DELTA_CAMERA_X)
	{
		_vy = playerY - haftWndHeight - cameraY - DELTA_CAMERA_X;
	}

	//------------- top
	if(playerY < cameraY + DELTA_CAMERA_Y)
	{
		_vy = playerY - DELTA_CAMERA_Y - cameraY;
	}
	
	//-----------------------------------------------------
	_rectCamera.Left		+= 0.1 * _vx;
	_rectCamera.Right		+= 0.1 * _vx;
	
	_rectCamera.Top			+= 0.1 * _vy;
	_rectCamera.Bottom		+= 0.1 * _vy;
	//-----------------------------------------------------

	//too top
	if(_rectCamera.Top < 0)
	{
		_rectCamera.SetY(0);
	}

	//too right
	if(_rectCamera.Right > GL_MapW)
	{
		_rectCamera.SetX(GL_MapW - GL_Width);
	}

	//too left
	if(_rectCamera.Left < 0)
	{
		_rectCamera.SetX(0);
	}

	//too bottom
	if(_rectCamera.Bottom > GL_MapH)
	{
		_rectCamera.SetY(GL_MapH - GL_Height);
	}

}


CRECT Camera::GetCameraExpand()
{
	CRECT r = _rectCamera;
	
	if(r.Left >= EXPAND_CAMERA)
		r.Left -= EXPAND_CAMERA;
	else
		r.Left = 0;
	
	if(r.Right <= GL_MapW - EXPAND_CAMERA)
		r.Right += EXPAND_CAMERA;
	else
		r.Right = GL_MapW;

	if(r.Top >= EXPAND_CAMERA)
		r.Top -= EXPAND_CAMERA;
	else
		r.Top = 0;
	
	if(r.Bottom <= GL_MapH - EXPAND_CAMERA)
		r.Bottom += EXPAND_CAMERA;
	else
		r.Bottom = GL_MapH;

	return r;
}