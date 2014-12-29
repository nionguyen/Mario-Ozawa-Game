#pragma once

#include "MyObject.h"
#include <vector>
using namespace std;

//size to limit the number of time we devide a node.
//if it's size equal or less than MIN_NODE_SIZE, it won't be devide to childnode
#define MIN_NODE_SIZE	100 //px

//Manage a rect in map with all object in it
class QuadTreeNode
{
protected:
	//all object belong it, except object in child node
	vector<MyObject*>*	_content;

	//all child node belong it
	QuadTreeNode*		_listChild; //4
	
	//init _listChild
	void CreateSubNodes ();
	
public:
	CRECT _bound;
	QuadTreeNode();
	~QuadTreeNode(void);

	//insert new object to this node
	void Insert (MyObject* obj);

	//get and remove all obj and obj in child node
	vector<MyObject*>* QueryObj (CRECT area);

	//get, DO NOT remove obj and obj in child node
	vector<MyObject*>* GetObj (CRECT area);
};

