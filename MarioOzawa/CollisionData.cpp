#include "CollisionData.h"


CollisionData::CollisionData(EObject ID,EDirect dirCollision,float deltaX,float deltaY,float delta,int indexObject)
{
	_ID = ID;
	_dirCollision = dirCollision;
	_deltaX = deltaX;
	_deltaY = deltaY;
	_delta = delta;
	_indexObject = indexObject;
}

CollisionData::~CollisionData(void)
{
}
