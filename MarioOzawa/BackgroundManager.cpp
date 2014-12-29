#include "BackgroundManager.h"
#include "Global.h"
#include "Texture.h"
#include "ResourceManager.h"

#define DEFAULT_TIME_ANI (100)
#define DEFAULT_DEPTH (0.9)
#define BG_EXPAND_X 17		//camera sẽ được mở rộng ra vài ô để có thể vẽ được hết cái núi
#define BG_EXPAND_Y 0		//camera sẽ được mở rộng ra vài ô để có thể vẽ được hết cái núi

BackgroundManager::BackgroundManager()
{
	_mapW = 0;
	_mapH = 0;
	_board = NULL;
}

BackgroundManager::~BackgroundManager()
{
	delete[] _board;
	delete[] _boardSprite;
	_board = NULL;
	_boardSprite = NULL;
}

void BackgroundManager::Translate()
{
	//create array
	_boardSprite = new Sprite**[_mapH];
	for(int i = 0; i < _mapH; i++)
	{
		_boardSprite[i] = new Sprite*[_mapW];
	}

	ResourceMng* rm = ResourceMng::GetInst();
	char name[50];

	//load sprite to array
	for (int i = 0; i < _mapH; ++i)
	{
		for (int j = 0; j < _mapW; ++j)
		{
			if(_board[i][j] != 0)
			{
				sprintf(name, "tile/%d.png", _board[i][j]);
				_boardSprite[i][j] = new Sprite(rm->GetTexture(name), DEFAULT_TIME_ANI);
			}
		}
	}
}

void BackgroundManager::UpdateRender(CRECT camera, int time)
{
	if(_board == NULL)
		return;
	//
	int startX = camera.Left / TILE - BG_EXPAND_X;
	startX = (startX < 0) ? 0 : startX;
	int endX = camera.Right / TILE + BG_EXPAND_X;
	endX = (endX > _mapW) ? _mapW : endX;

	int startY = camera.Top / TILE - BG_EXPAND_Y;
	startY = (startY < 0) ? 0 : startY;
	int endY = camera.Bottom / TILE + BG_EXPAND_Y;
	endY = (endY > _mapH) ? _mapH : endY;
	
	for(int i = startY; i < endY; ++i)
	{
		for(int j = startX; j < endX; ++j)
		{
			if(_board[i][j] != 0)
			{
				_boardSprite[i][j]->Update(time);

				//draw special pipe
				if(_board[i][j] >= 28 && _board[i][j] <= 32)
				{
					if(_board[i][j] != 32)
					{
						_boardSprite[i][j]->Render(j * TILE, i * TILE, 0.4f);
					}
					else
					{
						_boardSprite[i][j]->Render(j * TILE, i * TILE, 0.35f);
					}
				}
				else
				{
					_boardSprite[i][j]->Render(j * TILE, i * TILE);
				}
			}
		}
	}
}




