#include "TileMap.h"

TileMap* TileMap::_instance = NULL;
int** TileMap::_board = NULL;
int TileMap::_mapW = 0;
int TileMap::_mapH = 0;

TileMap::TileMap(void)
{
}

TileMap::~TileMap(void)
{
}

TileMap* TileMap::GetInst()
{
	if(_instance == NULL)
	{
		_instance = new TileMap();
	}

	return _instance;
}

void TileMap::RemoveTileAt(int posxPixel, int posyPixel)
{
	int column = posxPixel / TILE;
	int row = posyPixel / TILE;

	if(column >= 0 && column < _mapW && row >= 0 && row < _mapH)
		_board[row][column] = 0;
}