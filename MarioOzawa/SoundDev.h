#pragma once

#ifndef _DSOUND_H_
#define _DSOUND_H_


#include "dsutil.h"
#include "dxutil.h"


class DSound
{
private:
	HWND phwnd;
	CSoundManager* pDSound; 
public:
	DSound(void);
	~DSound(void);
	bool Init (HWND _hwnd);
	CSound* LoadSound(char* filename);
	void Destroy ();
};
#endif