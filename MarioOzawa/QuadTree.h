#pragma once

#include "QuadTreeNode.h"
#include "MyObject.h"
#include "Mario.h"

//size expand camera to update and check collision
//if the rect is equal SCREEN(800x600), some object out of it will be stop working, and it is so urgly
#define COLLIDE_EXPAND 5

//object id from MIN to MAX, follow all picture in folder "/image"
#define MIN_OBJ_ID 151
#define MAX_OBJ_ID 159

//Manage all game object
//Coroperate with camera to manage the view in map
class QuadTree
{
public:
	//Root node, contain all other node
	static QuadTreeNode* _rootNode;

	//rect in Rootnode, equal map size!
	static CRECT _bound;

	QuadTree(CRECT bound);
	~QuadTree(void);

	//insert new object
	static void Insert (MyObject* obj);

	//update all obj in quad tree
	void UpdateRender(CRECT camera, Mario* mario, int time);
};

