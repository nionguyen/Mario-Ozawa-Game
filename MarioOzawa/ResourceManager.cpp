#include "ResourceManager.h"
#include <string.h>

ResourceMng* ResourceMng::_instance = NULL;

ResourceMng::ResourceMng()
{
	//SURFACE
	_listSurface.push_back(new SURFACE("image/imgBgGame.png"));
	_listSurface.push_back(new SURFACE("image/imgBgGame2.png"));
	_listSurface.push_back(new SURFACE("image/imgBgMenu.png"));
	_listSurface.push_back(new SURFACE("image/imgBgOption.png"));
	_listSurface.push_back(new SURFACE("image/imgBgCredit.png"));

	//TEXTURE
	//intro sence
	_listTexture.push_back(new TEXTURE("image/imgLogo.png", 1, 1, 1));
	//---end intro

	//play sence
	//---end play

	//selectworld sence
	_listTexture.push_back(new TEXTURE("image/imgFlying.png", 9, 1, 9));
	//---end selectworld

	//menu sence
	_listTexture.push_back(new TEXTURE("image/imgItemPlay.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/imgItemOption.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/imgItemQuit.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/imgMarioHead.png", 2, 1, 2));
	//---end menu

	//option sence
	_listTexture.push_back(new TEXTURE("image/imgYes.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/imgNo.png", 1, 1, 1));
	//---end option

	//credit sence
	//---end credit

	//change map
	_listSurface.push_back(new SURFACE("image/change_map.png"));
	_listTexture.push_back(new TEXTURE("image/fire_to_start.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/ball.png", 1, 1, 1));
	//---end change map

	//zoom
	_listTexture.push_back(new TEXTURE("image/imgZoom.png", 1, 1, 1));
	//---end zoom

	//object in main game
	//TEXTURE
	_listTexture.push_back(new TEXTURE("image/Boss.png", 4, 1, 4));
	_listTexture.push_back(new TEXTURE("image/FireBoss.png", 3, 1, 3));
	_listTexture.push_back(new TEXTURE("image/TreeMonster.png", 4, 1, 4));

	_listTexture.push_back(new TEXTURE("image/MarioSmaller.png", 6, 1, 6));
	_listTexture.push_back(new TEXTURE("image/MarioLarger.png", 6, 1, 6));
	_listTexture.push_back(new TEXTURE("image/MarioFire.png", 6, 1, 6));

	_listTexture.push_back(new TEXTURE("image/brick.png", 2, 1, 2));
	_listTexture.push_back(new TEXTURE("image/Brick_Break.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/Coin.png", 7, 1, 7));
	_listTexture.push_back(new TEXTURE("image/Fungi.png", 3, 1, 3));
	_listTexture.push_back(new TEXTURE("image/turtle.png", 5, 1, 5));
	_listTexture.push_back(new TEXTURE("image/pipe.png", 1, 1, 1));
	_listTexture.push_back(new TEXTURE("image/Question.png", 3, 1, 3));

	_listTexture.push_back(new TEXTURE("image/Flower.png", 4, 1, 4));
	_listTexture.push_back(new TEXTURE("image/Lager.png", 2, 1, 2));
	_listTexture.push_back(new TEXTURE("image/Bullet.png", 10, 1, 10));
	//end object in game


	//other
	_listTexture.push_back(new TEXTURE("image/imgChar1.png", 12, 8, 96));
	_listTexture.push_back(new TEXTURE("image/imgChar2.png", 10, 10, 96));

	//background image
	for (int i = MIN_BG_ID; i <= MAX_BG_ID; ++i)
	{
		char* fileName;
		fileName = new char[50];
		sprintf(fileName, "tile/%d.png", i);
		//
		if(i == 15 || i == 18) //cloud, grass
		{
			_listTexture.push_back(new TEXTURE(fileName, 3, 1, 3));
		}
		else
		{
			_listTexture.push_back(new TEXTURE(fileName, 1, 1, 1));
		}
	}

	//ground image
	for (int i = MIN_GROUND_ID; i <= MAX_GROUND_ID; ++i)
	{
		char* fileName;
		fileName = new char[50];
		sprintf(fileName, "tile/%d.png", i);
		//
		_listTexture.push_back(new TEXTURE(fileName, 1, 1, 1));
	}
}

ResourceMng::~ResourceMng(void)
{
	if( ! _listTexture.empty()) _listTexture.clear();
	if( ! _listSurface.empty()) _listSurface.clear();
}

void ResourceMng::Release()
{
	if( ! _listTexture.empty()) _listTexture.clear();
	if( ! _listSurface.empty()) _listSurface.clear();
}

TEXTURE* ResourceMng::GetTexture(char*  fileName){
	int size = _listTexture.size();
	TEXTURE* tt;

	for(int i = 0 ; i < size; ++i){
		tt = _listTexture[i];

		if(strcmp(tt->FileName, fileName) == 0)
		{
			return tt;
		}
	}

	char t[100];
	sprintf(t, "[resourceMng.cpp] Can not get Texture[%s]", fileName);

	GLMessage(t);
	return NULL;
}

SURFACE* ResourceMng::GetSurface(char*  fileName){
	int size = _listSurface.size();
	SURFACE* sf;

	for(int i = 0 ; i < size; ++i){
		sf = _listSurface[i];
		if(strcmp(sf->FileName, fileName) == 0)
		{
			return sf;
		}
	}

	char t[100];
	sprintf(t, "[resourceMng.cpp] Can not get Surface:[%s]", fileName);
	GLMessage(t);

	return NULL;
}

ResourceMng* ResourceMng::GetInst(){
	if(_instance == NULL){
		_instance = new ResourceMng();
	}

	return _instance;
}

