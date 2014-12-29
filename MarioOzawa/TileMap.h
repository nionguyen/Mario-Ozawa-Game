#pragma once

#include "Rect.h"
#include "Global.h"

//id of tile in MAP file
#define MIN_TILE_ID 101
#define MAX_TILE_ID 106

//Save an array of byte to check if have any obj in a position in map
//+ do not Render any thing
//+ all things in this will be Rendered by background manager
//Implement singleton design pattern
class TileMap
{
public:
	//with of map counted by TILE (1 TILE = 50px x 50px)
	static int _mapW; 
	static int _mapH;

	//array 2 dimention type char to save id of TILE
	static int **_board;
	static TileMap* _instance;
	static TileMap* GetInst();

	//delete a tile in position (int posxPixel, int posyPixel)
	static void RemoveTileAt(int posxPixel, int posyPixel);

	~TileMap(void);

private:
	TileMap(void);
};
