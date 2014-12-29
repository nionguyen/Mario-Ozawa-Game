#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "QuadTree.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "Mario.h"

#ifndef TIME_FOR_LEVEL
	#define TIME_FOR_LEVEL 150000
#endif

//load map from a bitmap
//+ save it to an array
//+ translate it to obj (add to quadtree, backgroundManader), or tile map(to check collision)
class MapLoader
{
public:
	static LPDIRECT3DTEXTURE9 _mapTexture;
	static int _mapW;	//number tile in width
	static int _mapH;	//number tile in heigh

	static int _mapNumber; //số thứ tự của map
	static int _gold;
	static int _life;
	static int _exp;
	static int _curForm;
	static int _nextForm;
	static int _marioState; //state of mario
	static int _timeInGame;

	static int _mariox; //vị trí của mario
	static int _marioy;

	static int **_board ;	//2dimention array to saved id of object in map
	static int **_boardState; //2dimention array to state of object in map

	MapLoader(void);
	~MapLoader(void);

	//load save status, befrore call load file map
	//before call LoadMapFromFile
	static void LoadSavedGameFormFile(LPCTSTR filesavegame);

	//load map from an bitmap, save id(int) to array **_terrain
	//after call LoadSavedGameFromFile
	static HRESULT LoadMapFormFile (int mapNumber, bool isLoadMario, bool isLoadBackground, bool isLoadObjects, bool isLoadTileMap);

	//translate from _board to object, or save to BackgroundManager and TileMap
	static void TranslateMap (QuadTree* quadtree, BackgroundManager* background, Mario* mario, int &timeInGame);

	//save game to file
	static void SaveGameToFile(QuadTree* quadtree, Mario* mario, int timeInGame, LPCTSTR fileToSave);

	//delete all saved game file and reset static value in MapLoader
	static void DeleteSavedGame(LPCTSTR fileSavedGame);
};

