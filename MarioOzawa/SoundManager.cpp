#include "SoundManager.h"
#include "Global.h"

SoundManager* SoundManager::_instance = NULL;

SoundManager* SoundManager::GetInst()
{
	if(SoundManager::_instance == NULL)
	{
		_instance = new SoundManager();
	}

	return _instance;
}

SoundManager::SoundManager()
{
	SDev = new DSound;
	SDev->Init(GL_HWND);

	//effect sound
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_BOSS_FIRE));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_BOSS_HURT));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_BOSS_BEFORE_DIE));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_BOSS_DIE));	
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_SLIDE));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_PIPE));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_BRICK_UP));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_TOUCH_TIRTLE));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_EAT));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_UP));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_MUSH_DIE));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_SHOT));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_BROKEN));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_WIN));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_DEATH_SHOT));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_JUMP));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_DEATH));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_GROW));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_COIN));
	//_listEffSound.push_back(SDev->LoadSound(SOUND_E_1UP));
	_listEffSound.push_back(SDev->LoadSound(SOUND_E_CLICK));
	
	//background sound (mean loop)
	_listBgSound.push_back(SDev->LoadSound(SOUND_B_OPTION_STATE));
	//_listBgSound.push_back(SDev->LoadSound(SOUND_B_LOADING_STATE));
	//_listBgSound.push_back(SDev->LoadSound(SOUND_B_ABOUT_STATE));
	//_listBgSound.push_back(SDev->LoadSound(SOUND_B_LOSE_STATE));
	//_listBgSound.push_back(SDev->LoadSound(SOUND_B_WIN_STATE));
	//_listBgSound.push_back(SDev->LoadSound(SOUND_B_GAME2));
	_listBgSound.push_back(SDev->LoadSound(SOUND_B_GAME1));
	_listBgSound.push_back(SDev->LoadSound(SOUND_B_MENU));

	//TODO: add new sound here
}

SoundManager::~SoundManager()
{
	_listBgSound.clear();
	_listEffSound.clear();
}

void SoundManager::PlayEffSound(char* SOUND_FILE_PATH, bool isLoop)
{
	//check whether can play background sound
	if(! GL_HasEffectSound)
		return;

	int size = _listEffSound.size();

	for(int i = 0 ; i < size; ++i){
		if(strcmp(_listEffSound[i]->m_fileName, SOUND_FILE_PATH) == 0)
		{
			//_listEffSound[i]->Stop();
			if(isLoop)
			{
				_listEffSound[i]->Play(0, DSBPLAY_LOOPING);
			}
			else
			{
				_listEffSound[i]->Play();
			}
			return;
		}
	}

	char t[100];
	sprintf(t, "[SoundGame.cpp/PlayEffSound] Can not PlaySound[%s]", SOUND_FILE_PATH);

	GLMessage(t);
}

void SoundManager::PlayBgSound(char* SOUND_FILE_PATH, bool isLoop, bool wantPlayAgain)
{
	//check whether can play background sound
	if(! GL_HasBGSound)
		return;

	int size = _listBgSound.size();

	for(int i = 0 ; i < size; ++i){
		if(strcmp(_listBgSound[i]->m_fileName, SOUND_FILE_PATH) == 0)
		{
			if(wantPlayAgain)
			{
				_listBgSound[i]->Stop();
				_listBgSound[i]->Reset();
			}
			//
			if(isLoop)
			{
				_listBgSound[i]->Play(0, DSBPLAY_LOOPING);
			}
			else
			{
				_listBgSound[i]->Play();
			}
			return;
		}
	}

	char t[100];
	sprintf(t, "[SoundGame.cpp/PlayBgSound] Can not PlaySound[%s]", SOUND_FILE_PATH);

	GLMessage(t);
}

void SoundManager::StopBgSound(char* SOUND_FILE_PATH)
{
	int size = _listBgSound.size();

	for(int i = 0 ; i < size; ++i){
		if(strcmp(_listBgSound[i]->m_fileName, SOUND_FILE_PATH) == 0)
		{
			_listBgSound[i]->Stop();
			return;
		}
	}

	char t[100];
	sprintf(t, "[SoundGame.cpp/StopBgSound] Can not StopSound[%s]", SOUND_FILE_PATH);

	GLMessage(t);
}

void SoundManager::StopEffSound(char* SOUND_FILE_PATH)
{
	int size = _listEffSound.size();

	for(int i = 0 ; i < size; ++i){
		if(strcmp(_listEffSound[i]->m_fileName, SOUND_FILE_PATH) == 0)
		{
			_listEffSound[i]->Stop();
			return;
		}
	}

	char t[100];
	sprintf(t, "[SoundGame.cpp/StopEffSound] Can not StopSound[%s]", SOUND_FILE_PATH);

	GLMessage(t);
}

void SoundManager::StopAllBgSound()
{
	int size = _listBgSound.size();

	for(int i = 0 ; i < size; ++i){
		_listBgSound[i]->Stop();
	}
}

void SoundManager::StopAllEffSound()
{
	int size = _listEffSound.size();

	for(int i = 0 ; i < size; ++i){
		_listEffSound[i]->Stop();
	}
}
