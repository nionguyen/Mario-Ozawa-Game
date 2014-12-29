#include "QuadTree.h"
#include "Global.h"

//init static member

QuadTreeNode* QuadTree::_rootNode = NULL;
CRECT QuadTree::_bound = CRECT(0, 0, 0, 0);


QuadTree::QuadTree(CRECT bound)
{
	_bound = bound;
	_rootNode = new QuadTreeNode();
	_rootNode->_bound = bound;
}

QuadTree::~QuadTree(void)
{
	if(_rootNode != NULL)
	{
		delete _rootNode;
		_rootNode = NULL;
	}
}

void QuadTree::Insert (MyObject* obj)
{
	_rootNode->Insert(obj);
}

void QuadTree::UpdateRender(CRECT camera, Mario* mario, int time)
{
#pragma region create rect camera
	CRECT cameraCollision = camera;
	if(cameraCollision.Left >= COLLIDE_EXPAND)
		cameraCollision.Left -= COLLIDE_EXPAND;
	else
		cameraCollision.Left = 0;

	if(cameraCollision.Right <= GL_MapW - COLLIDE_EXPAND)
		cameraCollision.Right += COLLIDE_EXPAND;
	else
		cameraCollision.Right = GL_MapW;

	if(cameraCollision.Top >= COLLIDE_EXPAND)
		cameraCollision.Top -= COLLIDE_EXPAND;
	else
		cameraCollision.Top = 0;

	if(cameraCollision.Bottom <= GL_MapH - COLLIDE_EXPAND)
		cameraCollision.Bottom += COLLIDE_EXPAND;
	else
		cameraCollision.Bottom = GL_MapH;
#pragma endregion

	vector<MyObject*>* listCollision = this->_rootNode->GetObj(camera);
	vector<MyObject*>* listUpdate1 = this->_rootNode->GetObj(camera);
	vector<MyObject*>* listUpdate = this->_rootNode->QueryObj(camera);
	mario->UpdateRealTimeCollision(time,listUpdate);
	if(mario->_State != dead)
		listUpdate1->push_back(mario);
	for (std::vector<MyObject*>::iterator i = listUpdate->begin(); 
		i != listUpdate->end(); ++i)
	{
		//update
		//if((*i)->_ID != FUNGI) && ((*i)->_ID != f)
		//(*i)->Update(time);
		//else 
		{
			//vector<MyObject*>* listUpdate1 = new vector<MyObject*>;
			//listUpdate1 = listUpdate;
			//listUpdate1->push_back(mario);
			//(*i)->Update(time);
			//listCollision->erase(i);
			//mario->CheckCollision(*i);
			if(  ((*i)->_ID == EObject::ITEM) || ((*i)->_ID == EObject::FUNGI) || ((*i)->_ID == EObject::TURTLE) || ((*i)->_ID == EObject::BRICKITEM) || ((*i)->_ID == EObject::BRICKBREAK))
				(*i)->UpdateRealTimeCollision(time, listUpdate1);
			else (*i)->Update(time);
			if(((*i)->_ID == EObject::FUNGI) || ((*i)->_ID == EObject::TURTLE))
			{
				mario->CheckCollision(*i);
			}
			//listCollision->push_back(*i);
		}
		//check collision

		if((*i)->CanCollide())
		{
			//check collision with mario
			//(*i)->CheckCollision(mario);
			//mario->CheckCollision((*i));
			//if((*i)->_ID == TURTLE)
			//(*i)->CheckCollision(mario);
			if(((*i)->_ID == EObject::FUNGI) || ((*i)->_ID == EObject::TURTLE))
				(*i)->CheckCollision(mario);
			for (std::vector<MyObject*>::iterator j = listCollision->begin(); 
				j != listCollision->end(); ++j)
			{
				if((*i)->_ID == BRICKBREAK)
					if(*i != *j)
					{
						(*i)->CheckCollision(*j);
					}
			}
		}

		// fix lan 1
		// render
		(*i)->Render();

		// insert again
		if((*i)->IsAlive())
		{
			this->Insert(*i);
		}
	}
}
