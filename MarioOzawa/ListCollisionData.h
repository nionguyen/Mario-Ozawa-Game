#include "CollisionData.h"
#include <vector>
using namespace std;
//using namespace std;
#pragma once
class ListCollisionData
{
public:	//list object va cham truoc khi loc
	vector <CollisionData*> _listOldData;

	//list object sau khi loc ra nhung object thuc su va cham
	vector <CollisionData*> _listNewData;

	ListCollisionData(void);
	void add(CollisionData *_data);
	void clear();
	bool check();
	~ListCollisionData(void);
};

