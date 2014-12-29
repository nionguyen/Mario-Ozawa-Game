#pragma once

#include "MapLoader.h"
#include "Global.h"
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
 int MapLoader::_mapNumber = 0; //số thứ tự của map
 int MapLoader::_gold = -1;
 int MapLoader::_life = -1;
 int MapLoader::_exp = -1;
 int MapLoader::_curForm = -1;
 int MapLoader::_nextForm = -1;
 int MapLoader::_marioState = -1; //state of mario
 int MapLoader::_timeInGame = -1;

 int MapLoader::_mariox = 2; //vị trí của mario TILE
 int MapLoader::_marioy = 2;

 int** MapLoader::_board = NULL;
 int** MapLoader::_boardState = NULL;
 LPDIRECT3DTEXTURE9 MapLoader::_mapTexture = NULL;

MapLoader::MapLoader(void)
{
}

MapLoader::~MapLoader(void)
{
	delete _mapTexture;
	delete[] _board;
	delete[] _boardState;

	_mapTexture = NULL;
	_board = NULL;
	_boardState = NULL;
}

void MapLoader::LoadSavedGameFormFile(LPCTSTR _filesavegame)
{
	ifstream fin(_filesavegame);

	//có lưu
	if(fin != NULL)
	{
		//read file
		//dòng 1: map thứ mấy:
		fin>> _mapNumber;

		//gold
		fin>> _gold;

		//life
		fin>> _life;

		//exp
		fin>> _exp;

		//curForm
		fin>> _curForm;

		//nextForm
		fin>> _nextForm;

		//state
		fin>> _marioState;

		//time in game
		fin>> _timeInGame;

		//read mario x, y
		fin>> _mariox;
		fin>> _marioy;

		//load map from file map
		char mapfile[50];
		sprintf(mapfile, "map%d.png", _mapNumber);
		LoadMapFormFile(_mapNumber, false, true, false, false);

		//read game state
		//add to quadtree
		int id;
		int x;
		int y;
		int state;

		while(!fin.eof())
		{
			fin>> id;
			fin>> x;
			fin>> y;
			fin>> state;

			//add to board
			_board[y][x] = id;
			_boardState[y][x] = state;
		}
	}
	else
	{
		_mapNumber = 1;

		//load map from file map
		LoadMapFormFile(_mapNumber, true, true, true, true);
	}

	fin.close();
}

HRESULT MapLoader::LoadMapFormFile (int mapNumber, bool isLoadMario, bool isLoadBackground, bool isLoadObjects, bool isLoadTileMap)
{
	_mapNumber = mapNumber;

	HRESULT	hr;
	D3DXIMAGE_INFO imageInfo;
	char fileName[50];
	sprintf(fileName, "map/map%d.png", mapNumber);
	hr = D3DXGetImageInfoFromFile( fileName , &imageInfo);

	if(FAILED(hr))
	{
		GLMessage("No map to load!!!");
		return hr;
	}

	//Create a raw map as a texture file with a 32-bit format
	hr = D3DXCreateTextureFromFileEx( 
		GLDevice ,							// DirectX device
		fileName ,							// File Path
		imageInfo.Width ,					// width
		imageInfo.Height ,					// Height
		imageInfo.MipLevels ,				// MipLevels
		D3DUSAGE_DYNAMIC ,					// D3DUSAGE
		D3DFMT_A8R8G8B8 ,					// Format
		D3DPOOL_DEFAULT  ,					// Pool
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
	
	//load pixel ID to board
	//
	D3DLOCKED_RECT		rect;
	D3DSURFACE_DESC		desc;
	DWORD				i,j;
	D3DCOLOR**			pColor;

	//First get the D3DSURFACE_DESC of this raw map
	hr = _mapTexture->GetLevelDesc( 0 , &desc );
	if(FAILED(hr))
		return hr;

	//We create a new D3DCOLOR 2D array has enough room to hold pixel color 
	pColor = new D3DCOLOR*[desc.Height];
	for ( i = 0 ; i < desc.Height ; ++i)
		pColor[i] = new D3DCOLOR[desc.Width];

	//Lock entire texture to read pixel
	hr = _mapTexture->LockRect( 0 , &rect , NULL , D3DLOCK_READONLY );
	if(FAILED(hr))
		return hr;

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
	_board = new int*[_mapH];
	_boardState = new int*[_mapH];

	for(int i = 0; i < _mapH; i++)
	{
		_board[i] = new int[_mapW];
		_boardState[i] = new int[_mapW];
	}

	//gan gia tri ve 0
	for (int i = 0 ; i < _mapH; i++)	{
		for (int j = 0 ; j < _mapW; j++)	{			 
			_board[i][j] = 0;

			//default state for all object
			_boardState[i][j] = (int)State::start;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	for (i = 0 ; i < _mapH ; ++i)
	{
		for ( j = 0 ; j < _mapW ; ++j)
		{
			D3DCOLOR color = (pColor[i][j]);
			int blue = (color & 0x000000ff);
			
			if(blue == 0)
				continue;

			//MARIO
			if(blue == 1)
			{
				if(isLoadMario)
				{
					_mariox = j;
					_marioy = i;
				}
			}

			//BACKGROUND ID
			if((blue >= MIN_BG_ID && blue <= MAX_BG_ID) ||
				blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				if(isLoadBackground)
				{
					_board[i][j] = blue;
				}
			}

			//TILE MAP && BACKGROUND
			//BrickItem
			if(blue == 151 || blue == 153 || blue == 155 || blue == 156 || blue == 157)
			{
				if(isLoadTileMap)
				{
					_board[i][j] = blue;
				}
			}

			//TILE MAP ID / in Background
			if(blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				if(isLoadTileMap)
				{
					_board[i][j] = blue;
				}
			}
			
			//OBJECT ID
			if(blue >= MIN_OBJ_ID && blue <= MAX_OBJ_ID)
			{
				if(isLoadObjects)
				{
					_board[i][j] = blue;
				}
			}
		}
	}

	return S_OK;
}

void MapLoader::TranslateMap (QuadTree* quadtree, BackgroundManager* background, Mario* mario, int &timeInGame)
{
	//
	background->_mapW = _mapW;
	background->_mapH = _mapH;

	//
	TileMap::GetInst()->_mapW = _mapW;
	TileMap::GetInst()->_mapH = _mapH;

	//init array
	background->_board = new int*[_mapH];
	TileMap::GetInst()->_board = new int*[_mapH];

	for(int i = 0; i < _mapH; i++)
	{
		background->_board[i] = new int[_mapW];
		TileMap::GetInst()->_board[i] = new int[_mapW];
	}

	//gan gia tri ve 0
	for (int i = 0 ; i < _mapH; i++)	{
		for (int j = 0 ; j < _mapW; j++)	{
			background->_board[i][j] = 0;
			TileMap::GetInst()->_board[i][j] = 0;
		}
	}

	//time in game
	if(_timeInGame > -1)
		timeInGame = _timeInGame;

	//mario
	mario->_x = _mariox * TILE;
	mario->_y = _marioy * TILE;

	if(_curForm > -1 && _nextForm > -1 && _gold > -1 && _life > -1 && _exp > -1 && _marioState > -1)
	{
		GL_CurForm = _curForm;
		GL_NextForm = _nextForm;

		mario->gold = _gold;
		mario->life = _life;
		mario->exp = _exp;
		mario->_State = (State)_marioState;
	}	

	//Insert Object
	int blue;
	for (int i = 0 ; i < _mapH ; ++i)
	{
		for (int j = 0 ; j < _mapW ; ++j)
		{
			blue = _board[i][j];

			if(blue == 0)
				continue;
			
			//BACKGROUND ID
			if((blue >= MIN_BG_ID && blue <= MAX_BG_ID) ||
				blue >= MIN_TILE_ID && blue <= MAX_TILE_ID)
			{
				background->_board[i][j] = blue;
			}
			
			//TILE MAP ID / in Background
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
					//also in tile map
					TileMap::GetInst()->_board[i][j] = 1;
					quadtree->Insert(new brickBreak(j * TILE, i * TILE, (State)_boardState[i][j]));
					break;

				case 152: //coin
					quadtree->Insert(new coin(j * TILE, i * TILE, (State)_boardState[i][j]));
					break;

				case 153: //flower
					//also in tile map
					TileMap::GetInst()->_board[i][j] = 1;
					quadtree->Insert(new brickItem(j * TILE, i * TILE, EBrickItemKind::FLOWER, (State)_boardState[i][j]));
					break;

				case 154: //fungi
					quadtree->Insert(new fungi(j * TILE, i * TILE, (State)_boardState[i][j]));
					break;

				case 155: //brick question
					//also in tile map
					TileMap::GetInst()->_board[i][j] = 1;
					quadtree->Insert(new brickQuestion(j * TILE, i * TILE, (State)_boardState[i][j]));
					break;

				case 156: //larger blue
					//also in tile map
					TileMap::GetInst()->_board[i][j] = 1;
					quadtree->Insert(new brickItem(j * TILE, i * TILE, EBrickItemKind::SHOOTER, (State)_boardState[i][j]));
					break;

				case 157: //larger red
					//also in tile map
					TileMap::GetInst()->_board[i][j] = 1;
					quadtree->Insert(new brickItem(j * TILE, i * TILE, EBrickItemKind::LARGER, (State)_boardState[i][j]));
					break;

				case 158: //turtle
					quadtree->Insert(new turtle(j * TILE, i * TILE, (State)_boardState[i][j]));
					break;

					//kind of item
				case 159: //item
					Item* item = new Item(j * TILE, i * TILE, (EBrickItemKind)_boardState[i][j]);
					item->_State = State::Move;
					quadtree->Insert(item);
					break;

				}
			}
		}
	}
}

void MapLoader::SaveGameToFile(QuadTree* quadtree, Mario* mario, int timeInGame, LPCTSTR fileToSave)
{
	ofstream fout(fileToSave, ios_base::trunc);

	if(fout != NULL)
	{
		//mapNumber
		fout<< _mapNumber << endl;

		//gold
		fout<< mario->gold << endl;

		//life
		fout<< mario->life << endl;

		//exp
		fout<< mario->exp << endl;

		//curForm
		fout<< GL_CurForm << endl;

		//nextForm
		fout<< GL_NextForm << endl;

		//state
		fout<< (int)mario->_State << endl;

		//time in game
		fout<< timeInGame << endl;

		//mario.x
		fout<< (int)((mario->_x + TILE/3) / TILE) << endl;

		//mario.y
		fout<< (int)(mario->_y / TILE) << endl;

		//read from quadtree
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = GL_MapW;
		rect.bottom = GL_MapH;

		vector<MyObject*>* listObject = quadtree->_rootNode->GetObj(rect);

		for (std::vector<MyObject*>::iterator i = listObject->begin(); 
			i != listObject->end(); ++i)
		{
			MyObject* obj = (MyObject*)(*i);

			switch (obj->_ID)
			{
			case EObject::BRICKBREAK: //151
				{
					fout<< 151 << " " << (int)(obj->_x/ TILE) << " " << (int)(obj->_y/ TILE) << " " << (int)(obj->_State) <<endl;
				}
				break;

			case EObject::BRICKITEM: //cục gạch có chứa các nấm, và hoa
				{
					brickItem* item = (brickItem*)obj;

					if (item->_kindofitem == EBrickItemKind::FLOWER) //153
					{
						fout<< 153 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) <<endl;
					} 
					else if (item->_kindofitem == EBrickItemKind::LARGER) //157
					{
						fout<< 157 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) <<endl;
					} 
					else if (item->_kindofitem == EBrickItemKind::SHOOTER) //156
					{
						fout<< 156 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) <<endl;
					}
				}
				break;

			case EObject::BRICKQUESTION: //155 // cục gạch có chứa vàng
				{
					fout<< 155 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) << endl;
				}
				break;

			case EObject::COIN: //152
				{
					fout<< 152 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) << endl;
				}
				break;

			case EObject::FUNGI: //154
				{
					fout<< 154 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) << endl;
				}
				break;

			case EObject::TURTLE: //158
				{
					fout<< 158 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(obj->_State) << endl;
				}
				break;

				//item not in map editor
			case EObject::ITEM: //159
				{
					Item* item = (Item*)(*i);
					fout<< 159 << " " << (int)(obj->_x / TILE) << " " << (int)(obj->_y / TILE) << " " << (int)(item->_item) << endl; //kindOfItem replace state
				}
				break;
			}
		}

		fout.close();
	}	
}

void MapLoader::DeleteSavedGame(LPCTSTR fileSavedGame)
{
	//delete savedgame file
	if( remove( "saved/savedgame.txt" ) != 0 )
	{
		//GLMessage("Delete savedgame.txt! successfull");
	}
	else
	{
		//GLMessage("Can not delete savedgame.txt!");
	}

	//reset all static value
	MapLoader::_mapW = 0;
	MapLoader::_mapH = 0;
	//MapLoader::_mapNumber = 0; //số thứ tự của map
	MapLoader::_gold = -1;
	MapLoader::_life = -1;
	MapLoader::_exp = -1;
	MapLoader::_curForm = -1;
	MapLoader::_nextForm = -1;
	MapLoader::_marioState = -1; //state of mario
	MapLoader::_timeInGame = -1;

	MapLoader::_mariox = 2; //vị trí của mario TILE
	MapLoader::_marioy = 2;

	MapLoader::_board = NULL;
	MapLoader::_mapTexture = NULL;
}
