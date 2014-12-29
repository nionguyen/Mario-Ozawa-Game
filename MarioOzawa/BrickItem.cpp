
#include "SoundManager.h"
#include "BrickItem.h"
#include "ResourceManager.h"
#include "TileMap.h"

brickItem::brickItem(float x, float y,EBrickItemKind kindOfItem,State state) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Question.png"), 500);
	_ID = EObject::BRICKITEM;
	_curSprite->SelectIndex(1);
	_curSprite->_start = 1;
	_curSprite->_end = 2;
	if(state == State::start)
		_State = hasItem;
	else _State = state;
	_kindofitem = kindOfItem;
	_x = x;
	_y = y;
	_item = new Item(_x + 5,_y,_kindofitem);
}


brickItem::~brickItem(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void brickItem::Update(int time)
{
	if(_State == hasItem)
	{
		_curSprite->Update(time);
	}
}

void brickItem::Render()
{
	if(_State == stand)
	{
		_curSprite->SelectIndex(0);
	}

	_curSprite->Render((int)_x, (int)_y);
}

void brickItem::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	if(_State == hasItem)
		_curSprite->Update(time);
	//else _item->UpdateRealTimeCollision(time,listcollision);
}

void brickItem::CheckCollision(MyObject* obj)
{
	/*if(_State != hasItem)
	{
		if((obj->_ID == EObject::BRICKBREAK) || (obj->_ID == EObject::MARIO))
			_item->CheckCollision(obj);
	}*/
}