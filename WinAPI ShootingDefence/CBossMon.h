#pragma once

#include "Vector2D.h"
#include "CUnit.h"

class CBossMon : public CUnit
{
	HWND m_hWnd = NULL;
	HBRUSH m_R_brsh;

	bool IsAppearState;		// 등장 완료 연출 상태인지를 확인하는 플래그

	Vector2D m_TargetPos;
	Vector2D m_DirVec;
	float m_SkillTime = 0.0f;
	int m_SkillCount = 0;
	float m_AttackSpeed = 1.0f;		// 공격속도
	float m_BLCycle = 0.0f;			// 공격주기 계산용 변수

public:
	bool m_isActive = false;

	Vector2D m_CurPos;
	float m_Speed = 300.0f;
	//------ 주인공 좌표 계산용 변수들...
	float m_HalfColl = 20.0f;		// 주인공과의 충돌 반경
	int m_CurHP;
	int m_MaxHP;
	//------ 주인공 좌표 계산용 변수들...

public:
	CBossMon();
	~CBossMon();

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void Spawn(float a_XX, float a_YY);
	bool BossLimitMove(RECT& a_RT);		// 보스가 등장하는 연출을 위해 밖에서 스폰되서 화면 안으로 들어오면 멈추게 처리하는 함수

	void TakeDamage(float a_Damage = 10.0f);
	void ReSrcClear();		// 라운드를 넘어갈때 필드에 등장해 있는 모든 보스 삭제 함수
	void SkillShoot();		// 보스 스킬 사용
};

