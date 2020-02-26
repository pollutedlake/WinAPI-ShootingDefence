#pragma once
#include "Vector2D.h"
#include "CUnit.h"

class CHero : public CUnit
{
	HWND m_hWnd;
	float m_Speed = 300.0f;

	//------ 쉴드 관련 변수
	float m_DeltaTime = 0.0f;
	//------ 쉴드 관련 변수

	float m_AttackSpeed = 0.1f;		// 공격속도
	float m_BLCycle = 0.0f;

public:
	int m_CurHP;
	int m_MaxHP;

private:
	HBRUSH m_R_brsh;
	HGDIOBJ m_R_Old_brsh;

	//------ 쉴드
	Image* m_Shield;
	float m_SdDuration = 8.0f;

public:
	float m_SdOnTime = 0.0f;
	float m_SdHalfSize;
	//------ 쉴드

	//------ 능력치
	float m_CurAttack = 10.0f;		// 주인공의 공격력
	int m_KillCount = 0;			// 킬 수
	int m_SkillCount = 5;			// 남은 스킬 수
	int m_ShieldCount = 5;			// 남은 보호막 수
	int m_MyMoney = 0;				// 유저의 골드
	//------ 능력치

public:
	Vector2D m_CurPos;
	float m_HalfColl = 20.0f;		// 주인공의 충돌 반경

	float m_STDelay = 0.5f;

public:
	CHero();
	~CHero();

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime, RECT& a_RT);
	void Render_Unit(HDC a_hdc);
	void Destroy_Unit();

	void HeroLimitMove(RECT& a_RT);

	void Load_Shield();
	void ShieldUpdate();
	void ShieldRender(Graphics& graphics);
	void ShieldDestroy();

	void TakeDamage(float a_Damage = 10.0f);

	static void BuyHP();
	static void BuySkill();
	static void BuyShield();
};

extern CHero g_Hero;