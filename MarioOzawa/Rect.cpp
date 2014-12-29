#include "Rect.h"
#include <math.h>


CRECT::CRECT(void)
{
	Left	= 0;
	Right	= 0;
	Top		= 0;
	Bottom	= 0;
}

CRECT::CRECT(RECT r)
{
	Left	= r.left;
	Top		= r.top;
	Right	= r.right;
	Bottom	= r.bottom;
}

//LEFT - TOP- RIGHT - BOTTOM
CRECT::CRECT(float left, float top, float right, float bottom)
{
	Left	= left;
	Right	= right;
	Top		= top;
	Bottom	= bottom;
}

CRECT::~CRECT(void)
{
}

RECT CRECT::ToRECT()
{
	RECT r = {Left, Top, Right, Bottom};
	return r;
}

//collision
bool CRECT::IsCollision(CRECT rect)
{
	bool c1 = (rect.Left >= Left)
		&&(rect.Right <= Right)
		&&(rect.Top >= Top)
		&&(rect.Bottom <= Bottom);

	float dh = (fabs(Top-rect.Bottom) > fabs((Bottom-rect.Top))) ? fabs(Top-rect.Bottom) : fabs((Bottom-rect.Top));
	float dw = (fabs(Left - rect.Right) > fabs(Right - rect.Left)) ? fabs(Left-rect.Right) : fabs(Right - rect.Left);

	return ((dw <= ((Right-Left)+(rect.Right-rect.Left)))&&
		(dh <= ((Bottom-Top) + (rect.Bottom- rect.Top))) || c1);
}

void CRECT::Move(float x, float y)
{
	Left	+= x;
	Right	+= x;
	Top		+= y;
	Bottom	+= y;
}

void CRECT::SetX(float x)
{
	float dx = x - Left;
	Left	+= dx;
	Right	+= dx;
}

void CRECT::SetY(float y)
{
	float dy = y - Top;
	Top		+= dy;
	Bottom	+= dy;
}
