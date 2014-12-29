#pragma once

#include "_MapLoader.h"
#include "Global.h"
#include "Brick.h"
#include "BrickBreak.h"
#include "BrickItem.h"
#include "BrickQuestion.h"
#include "Turtle.h"
#include "Coin.h"
#include "Fungi.h"

//macro to get byte in color
#define getA© ((©&0xff000000)>>24)
#define getR© ((©&0x00ff0000)>>16)
#define getG© ((©&0x0000ff00)>>8)
#define getB© (©&0x000000ff)

int MapLoader::_mapW = 0;
int MapLoader::_mapH = 0;

MapLoader::MapLoader(void)
{
	_mapW = 0;
	_mapH = 0;
}

MapLoader::~MapLoader(void)
{
	delete _mapTexture;
	delete[] _board;
}

HRESULT MapLoader::LoadMapFormFile(LPCTSTR file)
{
	HRESULT	hr;
	D3DXIMAGE_INFO imageInfo;
	hr = D3DXGetImageInfoFromFile( file , &imageInfo );

	if(FAILED(hr))
	{
		GLMessage("Load MAP failed!!!");
		return hr;
	}

	//Create a raw map as a texture file with a 32-bit format
	hr = D3DXCreateTextureFromFileEx( 
		GLDevice ,							// DirectX device
		file ,							    // File Path
		imageInfo.Width ,					// width
		imageInfo.Height ,					// Height
		imageInfo.MipLevels ,				// MipLevels
		D3DUSAGE_DYNAMIC ,					// D3DUSAGE
		D3DFMT_A8R8G8B8 ,					// Format
		D3DPOOL_DEFAULT ,					// Pool
		D3DX_DEFAULT ,						// Filter
		D3DX_DEFAULT ,						// Mip filter
		0 ,									// Color key
		&imageInfo ,						// Image Info
		NULL ,								// NULL
		&_mapTexture );						// Output texture

	//Store the raw map width and height
	_mapW	= imageInfo.Width;
	_mapH	= imageInfo.Height;

	GL_MapW = _mapW * TILE;
	GL_MapH = _mapH * TILE;

	GL_MapTileW = _mapW;
	GL_MapTileH = _mapH;

	if(FAILED(hr))
		return hr;

	return S_OK;
}

void MapLoader::TranslateMap (QuadTree* quadtree, BackgroundManager* background, Mario* mario)
{
	//
	background->_mapW = _mapW;
	background->_mapH = _mapH;

	//
	TileMap::GetInst()->_mapW = this->_mapW;
	TileMap::GetInst()->_mapH = this->_mapH;

	//
	HRESULT				hr;
	D3DLOCKED_RECT		rect;
	D3DSURFACE_DESC		desc;
	DWORD				i,j;
	D3DCOLOR**			pColor;

	//First get the D3DSURFACE_DESC of this raw map
	hr = _mapTexture->GetLevelDesc( 0 , &desc );
	if(FAILED(hr))
		return ;

	//We create a new D3DCOLOR 2D array has enough room to hold pixel color 
	pColor = new D3DCOLOR*[desc.Height];
	for ( i = 0 ; i < desc.Height ; ++i)
		pColor[i] = new D3DCOLOR[desc.Width];

	//Lock entire texture to read pixel
	hr = _mapTexture->LockRect( 0 , &rect , NULL , D3DLOCK_READONLY );
	if(FAILED(hr))
		return ;

	BYTE* pBits = (BYTE*)rect.pBits;

	for (i = 0 ; i < desc.Height ; ++i)
	{
		for ( j = 0 ; j < desc.Width ; ++j)
		{
			DWORD index =( j*4 + ( i * (rect.Pitch) ));

			// Blue
			BYTE b = pBits[index];

			// Green
			BYTE g = pBits[index+1];

			// Red
			BYTE r = pBits[index+2];

			// Alpha
			BYTE a = pBits[index+3];
			D3DCOLOR color = D3DCOLOR_ARGB(a , r , g , b );
			pColor[i][j] = color;
		}
	}
	//Unlock texture
	_mapTexture->UnlockRect(0);

	//----------------------
	_board = new char*[_mapH];

	background->_board = new char*[_mapH];
	TileMap::GetInst()->_board = new char*[_mapH];

	for(int i = 0; i < _mapH; i++)
	{
		_board[i] = new char[_mapW];

		background->_board[i] = new char[_mapW];
		TileMap::GetInst()->_board[i] = new char[_mapW];
	}

	//gan gia tri ve 0
	for (int i = 0 ; i < _mapH; i++)	{
		for (int j = 0 ; j < _mapW; j++)	{			 
			_board[i][j] = 0;

			background->_board[i][j] = 0;
			TileMap::GetInst()->_board[i][j] = 0;
		}
	}
	
	//Insert Object
	for (i = 0 ; i < _mapH ; ++i)
	{
		for ( j = 0 ; j < _mapW ; ++j)
		{
			D3DCOLOR color = (pColor[i][j]);
			int blue = (color & 0x000000ff);
			_board[i][j] = blue;

			//MARIO
			if(blue == 1)
			{
				mario->_x = j * TILE;
				mario->_y = i * TILE;
			}

			//BACKGROUND ID
			if((blue >= MIN_BG_ID && blue <= MAX_BG_ID) ||
				blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				background->_board[i][j] = blue;
			}
			
			//TILE MAP ID
			if(blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				TileMap::GetInst()->_board[i][j] = 1;
				
				if(blue == 103 || blue == 104 || blue == 105) //gound
				{
					if(i + 1 < _mapH)
						TileMap::GetInst()->_board[i + 1][j] = 1;
				}

				if(blue == 106) //pipe
				{
					if(i + 1 < _mapH && j + 1 < _mapW)
					{
						TileMap::GetInst()->_board[i + 1][j] = 1;
						TileMap::GetInst()->_board[i][j + 1] = 1;
						TileMap::GetInst()->_board[i + 1][j + 1] = 1;
					}

				}
			}

			//OBJECT ID
			if(blue >= MIN_OBJ_ID && blue <= MAX_OBJ_ID)
			{
				switch(blue)
				{
				case 151: //brick break
					quadtree->Insert(new brickBreak(j * TILE, i * TILE));
					break;

				case 152: //coin
					quadtree->Insert(new coin(j * TILE, i * TILE));
					break;

				case 153: //flower
					quadtree->Insert(new brickItem(j * TILE, i * TILE, 0));
					break;

				case 154: //fungi
					quadtree->Insert(new fungi(j * TILE, i * TILE));
					break;

				case 155: //brick question
					quadtree->Insert(new brickQuestion(j * TILE, i * TILE));
					break;

				case 156: //larger blue
					quadtree->Insert(new brickItem(j * TILE, i * TILE, 2));
					break;

				case 157: //larger red
					quadtree->Insert(new brickItem(j * TILE, i * TILE, 1));
					break;

				case 158: //turtle
					quadtree->Insert(new turtle(j * TILE, i * TILE));
					break;
				}
			}
		}
	}
}
