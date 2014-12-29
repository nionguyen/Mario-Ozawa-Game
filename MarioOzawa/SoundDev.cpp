#include "SoundDev.h"


DSound::DSound(void)
{
	pDSound = new CSoundManager();
}
DSound::~DSound(void)
{	
	Destroy();
}
bool DSound::Init(HWND _hwnd)
{
	phwnd=_hwnd;
	HRESULT hr=NULL ;
	hr=pDSound->Initialize(phwnd,DSSCL_PRIORITY);
	if(hr!=DS_OK)
	{
		MessageBox(phwnd,"Coudln't creata sound manager","Error",MB_OK);
		return 0;
	}
	hr=pDSound->SetPrimaryBufferFormat(2,22050,16);
	if(hr!=DS_OK)
	{
		MessageBox(phwnd,"Couln't set primary buffer format","Error",MB_OK);
		return 0;
	}
	return 1;
}
CSound* DSound::LoadSound(char* filename)
{
	CSound* wave;
	HRESULT hr=NULL;
	hr=pDSound->Create(&wave,filename);
	wave->m_fileName = filename;

	if(hr != DS_OK)
	{
		MessageBox(phwnd,"Coudln't create sound","Error",MB_OK);
		return NULL;
	}

	return wave;
}
void DSound::Destroy()
{
	if(pDSound!=NULL)
	{
		delete pDSound;
		pDSound = NULL;
	}
}