#pragma once

enum CT_Type {
	CT_None = 0,
	CT_Nanami,
	CT_Zombie1,
	CT_Zombie2,
	CT_Zombie3,
	CT_Zombie4,
	CT_Zombie5,
	CT_Zombie6,
	CT_Zombie8,
	CT_Boss,
	CT_Length,
};

enum AniState {
	AS_None,
	Idle,
	Front_Walk,
	Back_Walk,
	Left_Walk,
	Right_Walk,
	AniLength,
};

enum GameState {
	GAME_READY = 0,
	GAME_START,
	NEXT_LEVEL,
	GAME_OVER,
};

extern GameState g_GameState;

extern int g_TimeOut;
extern int g_DiffLevel;		// ≥≠¿Ãµµ