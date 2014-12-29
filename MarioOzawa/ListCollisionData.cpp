#include "ListCollisionData.h"


ListCollisionData::ListCollisionData(void)
{
}


ListCollisionData::~ListCollisionData(void)
{
}


// add object vo list object va cham truoc khi loc
void ListCollisionData::add(CollisionData *_data)
{
	_listOldData.push_back(_data);
}
void ListCollisionData::clear()
{
	_listOldData.clear();
	_listNewData.clear();
}
bool ListCollisionData::check()
{
	//buoc 1 :tim min delta
	//buoc 2 : tim nhung object nao co delta = min add vo newdata

	int size = _listOldData.size();
	if(size == 0)
		return false;
	/*CollisionData* sf;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listOldData[i];
		_listNewData.push_back(sf);
	}*/
	
	CollisionData* sf;
	float minDelta = _listOldData[0]->_delta;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listOldData[i];
		//sf->Render();
		if(minDelta > sf->_delta)
			minDelta = sf->_delta;
	}

	for(int j = 0; j < size; ++j )
	{
		sf = _listOldData[j];
		//if(sf->_delta == minDelta)
			_listNewData.push_back(sf);
	}

	return true;
}
