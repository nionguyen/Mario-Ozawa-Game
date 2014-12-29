#include "QuadTreeNode.h"


QuadTreeNode::QuadTreeNode()
{
	_content = new std::vector<MyObject*>();
	_listChild = NULL;
}

QuadTreeNode::~QuadTreeNode(void)
{
	if (_listChild != NULL)
	{
		delete[] _listChild;
		_listChild = NULL;
	}

	if (_content != NULL)
	{
		_content->clear();
		delete _content;
		_content = NULL;
	}
}

void QuadTreeNode::CreateSubNodes()
{
	 // the smallest sub node has an area 
	if (_bound.Right - _bound.Left < MIN_NODE_SIZE)
	{
		return;
	}

	if (_bound.Bottom - _bound.Top < MIN_NODE_SIZE)
	{
		return;
	}

	float halfWidth = (_bound.Right - _bound.Left) / 2;
	float halfHeight = (_bound.Bottom - _bound.Top) / 2;

	_listChild = new QuadTreeNode[4]();

	_listChild[0]._bound = (
		CRECT(
		_bound.Left, 
		_bound.Top, 
		_bound.Left + halfWidth, 
		_bound.Top + halfHeight));

	_listChild[1]._bound = (
		CRECT(
		_bound.Left + halfWidth, 
		_bound.Top,
		_bound.Right,
		_bound.Top + halfHeight));

	_listChild[2]._bound = (
		CRECT(
		_bound.Left,
		_bound.Top + halfHeight,
		_bound.Left + halfWidth,
		_bound.Bottom));

	_listChild[3]._bound = (
		CRECT(
		_bound.Left + halfWidth,
		_bound.Top + halfHeight,
		_bound.Right,
		_bound.Bottom));
}

void QuadTreeNode::Insert(MyObject* obj)
{
	if(! _bound.IsCollision(obj->GetRect()))
	{
		return;
	}

	//ko dc chia nho
	if (_bound.Right - _bound.Left < 2 * MIN_NODE_SIZE ||
		_bound.Bottom - _bound.Top < 2 * MIN_NODE_SIZE)
	{
		_content->push_back(obj);
		return;
	}
	else //dc chia nho
	{
		if(_listChild == NULL)
		{
			this->CreateSubNodes();
		}

		//dem so va cham
		int countCollision = 0;
		for(int i = 0; i < 4; ++i)
		{
			if(_listChild[i]._bound.IsCollision(obj->GetRect()))
			{
				countCollision++;
			}
		}

		if(countCollision >= 2)
		{//thuoc node hien tai
			_content->push_back(obj);
			return;
		}
		else
		{
			for(int j = 0; j < 4; ++j)
			{
				_listChild[j].Insert(obj);
			}
			return;
		}
	}
}

std::vector<MyObject*>* QuadTreeNode::QueryObj(CRECT area)
{
	std::vector<MyObject*> *result = new std::vector<MyObject*>();

	if (!_bound.IsCollision(area))
	{
		return result;
	}

	//add obj from this node
	for (std::vector<MyObject*>::iterator i = _content->begin(); 
		i != _content->end(); )
	{
		//intersect obj will be add
		if (area.IsCollision((*i)->GetRect()))
		{
			result->push_back((*i));

			i = _content->erase(i);
		} 
		else
		{
			i++;
		}
	}

	//add obj from sub node
	if (_listChild != NULL)
	{
		std::vector<MyObject*> *queryList;
		for (int i = 0 ; i < 4; i++)
		{			
			//collision node, check for sub node
			queryList = _listChild[i].QueryObj(area);
			result->insert(result->begin(), queryList->begin(), queryList->end());
			queryList->clear();
		}
		delete queryList;
		queryList = NULL;
	}

	return result;
}

vector<MyObject*>* QuadTreeNode::GetObj (CRECT area)
{
	std::vector<MyObject*> *result = new std::vector<MyObject*>();

	if (!_bound.IsCollision(area))
	{
		return result;
	}

	//add obj from this node
	for (std::vector<MyObject*>::iterator i = _content->begin(); 
		i != _content->end(); ++i)
	{
		//intersect obj will be add
		if (area.IsCollision((*i)->GetRect()))
		{
			result->push_back(*i);
		}
	}

	//add obj from sub node
	if (_listChild != NULL)
	{
		std::vector<MyObject*> *queryList;
		for (int i = 0 ; i < 4; i++)
		{			
			//collision node, check for sub node
			queryList = _listChild[i].GetObj(area);
			result->insert(result->begin(), queryList->begin(), queryList->end());
			queryList->clear();
		}
		delete queryList;
		queryList = NULL;
	}

	return result;
}