#pragma once


#ifndef _SOUNDGAME_H_
#define _SOUNDGAME_H_

#include "SoundDev.h"
#include <vector>
using namespace std;

#pragma region define

//#define SOUND_E_BOSS_FIRE 			"sound/e_boss_fire.wav"
//#define SOUND_E_BOSS_HURT 			"sound/e_boss_hurt.wav"
#define SOUND_E_BOSS_BEFORE_DIE 	 "sound/e_boss_before_die.wav"
//#define SOUND_E_BOSS_DIE 			"sound/e_boss_die.wav"
#define SOUND_B_OPTION_STATE 		"sound/b_option_state.wav"
//#define SOUND_B_LOADING_STATE 		"sound/b_loading_state.wav"
//#define SOUND_B_ABOUT_STATE 		"sound/b_about_state.wav"
//#define SOUND_B_LOSE_STATE 			"sound/b_lose_state.wav"
//#define SOUND_B_WIN_STATE 			"sound/b_win_state.wav"
#define SOUND_E_SLIDE 				"sound/e_slide.wav"
#define SOUND_E_PIPE 				"sound/e_pipe.wav"
//#define SOUND_E_BRICK_UP 			"sound/e_brick_up.wav"
#define SOUND_E_TOUCH_TIRTLE 		"sound/e_touch_tirtle.wav"
//#define SOUND_E_EAT 				"sound/e_eat.wav"
#define SOUND_E_UP 					"sound/e_up.wav"
#define SOUND_E_MUSH_DIE 			"sound/e_mush_die.wav"
#define SOUND_E_SHOT 				"sound/e_shot.wav"
#define SOUND_E_BROKEN 				"sound/e_broken.wav"
//#define SOUND_E_WIN 				"sound/e_win.wav"
#define SOUND_E_DEATH_SHOT 			"sound/e_death_shot.wav"
#define SOUND_E_JUMP 	 "sound/e_jump.wav"
#define SOUND_E_DEATH 	 "sound/e_death.wav"
#define SOUND_E_GROW 	 "sound/e_grow.wav"
#define SOUND_E_COIN 	 "sound/e_coin.wav"
//#define SOUND_E_1UP 	 "sound/e_1up.wav"
#define SOUND_E_CLICK 	 "sound/e_click.wav"
//#define SOUND_B_GAME2 	 "sound/b_game2.wav"
#define SOUND_B_GAME1 	 "sound/b_game1.wav"
#define SOUND_B_MENU 	 "sound/b_menu.wav"

#pragma endregion define

//Manage sound in game
//Load them
//Play them
//Implement singleton design pattern
class SoundManager
{
private:
	DSound* SDev;
	
	//List of effect sound
	vector<CSound*> _listEffSound;

	//List of background sound (looped play sound)
	vector<CSound*> _listBgSound;

	SoundManager();

	static SoundManager* _instance;

public:

	static SoundManager* GetInst();
	
	~SoundManager();
	
	//play background sound
	//loop by default
	//if this sound have played, 
	//wantPlayAgain: TRUE  => stop and play again
	//wantPlayAgain: FALSE => do not stop, continue that sound
	void PlayBgSound(char* SOUND_FILE_PATH, bool isLoop = true, bool wantPlayAgain = false);

	//play a effect sound, unloop by default
	void PlayEffSound(char* SOUND_FILE_PATH, bool isLoop = false);

	void StopBgSound(char* SOUND_FILE_PATH);

	void StopEffSound(char* SOUND_FILE_PATH);

	void StopAllBgSound();

	void StopAllEffSound();
};

#endif