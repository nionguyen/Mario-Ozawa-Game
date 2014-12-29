#include "Writer.h"

void Writer::RenderFont1(char* text, int x, int y, float scale)
{
	static Sprite* _sprText;
	_sprText = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgChar1.png"), 0);

	int CHAR_W = _sprText->_texture->Width - 18;
	int CHAR_H = _sprText->_texture->Height;
	int len = strlen(text);
	int index = 0;
	//
	for(int i = 0; i < len; ++i)
	{
		index = text[i] - ' ';
		_sprText->SelectIndex(index);

		//_sprText->Render(x + i * CHAR_W, y);
		_sprText->RenderTransform(x + i * CHAR_W * scale, y, D3DXVECTOR2(scale, scale), 0.0f, 0.0f);
	}
}

void Writer::RenderFont2(char* text, int x, int y, float scale)
{
	static Sprite* _sprText;
	_sprText = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgChar2.png"), 0);

	int CHAR_W = _sprText->_texture->Width - 28;
	int CHAR_H = _sprText->_texture->Height;
	int len = strlen(text);
	int index = 0;

	int curPos = x;

	//
	for(int i = 0; i < len; ++i)
	{
		index = text[i] - ' ';
		_sprText->SelectIndex(index);

		if((text[i] == 'l' || text[i] == 'i' || text[i] == 'j') || 
			((i - 1 > 0) &&  (text[i-1] == 'j' || text[i-1] == 'j' || text[i-1] == 'j')))
		{
			int charW = 2 * CHAR_W / 3;
			_sprText->RenderTransform(curPos + charW * scale, y, D3DXVECTOR2(scale, scale), 0.0f, 0.0f);
			curPos += charW * scale;
		}
		else
		{
			_sprText->RenderTransform(curPos + CHAR_W * scale, y, D3DXVECTOR2(scale, scale), 0.0f, 0.0f);
			curPos += CHAR_W * scale;
		}
	}
}