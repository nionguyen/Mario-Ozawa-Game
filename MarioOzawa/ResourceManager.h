#pragma once

#ifndef __RM_H__
#define __RM_H__

#include "Texture.h"
#include "Surface.h"

#include "Sprite.h"
#include <vector>
using namespace std;

//Manage a part of resource needed for game
//+texture
//+surface
//Implement singleton designe pattern
class ResourceMng
{
private:
	//load all resource
	ResourceMng();

	//unique instance
	static ResourceMng* _instance;

	//-------------------- RESOURCE ----------------------
	//List of surface
	vector<SURFACE*> _listSurface;

	//List of texture
	vector<TEXTURE*> _listTexture;

public:
	//release all resource
	~ResourceMng(void);

	void Release();

	//get the unique instance
	static ResourceMng* GetInst();

	//get surface
	SURFACE* GetSurface(char* fileName);

	//get texture
	TEXTURE* GetTexture(char* fileName);
};



#endif