#pragma once

#include "Vector2D.h"
#include "CUnit.h"

class CBossMon : public CUnit
{
	HWND m_hWnd = NULL;
	HBRUSH m_R_brsh;

	bool IsAppearState;		// ���� �Ϸ� ���� ���������� Ȯ���ϴ� �÷���

	Vector2D m_TargetPos;
	Vector2D m_DirVec;
	float m_SkillTime = 0.0f;
	int m_SkillCount = 0;
	float m_AttackSpeed = 1.0f;		// ���ݼӵ�
	float m_BLCycle = 0.0f;			// �����ֱ� ���� ����

public:
	bool m_isActive = false;

	Vector2D m_CurPos;
	float m_Speed = 300.0f;
	//------ ���ΰ� ��ǥ ���� ������...
	float m_HalfColl = 20.0f;		// ���ΰ����� �浹 �ݰ�
	int m_CurHP;
	int m_MaxHP;
	//------ ���ΰ� ��ǥ ���� ������...

public:
	CBossMon();
	~CBossMon();

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime);
	void Render_Unit(HDC a_hDC);
	void Destroy_Unit();

	void Spawn(float a_XX, float a_YY);
	bool BossLimitMove(RECT& a_RT);		// ������ �����ϴ� ������ ���� �ۿ��� �����Ǽ� ȭ�� ������ ������ ���߰� ó���ϴ� �Լ�

	void TakeDamage(float a_Damage = 10.0f);
	void ReSrcClear();		// ���带 �Ѿ�� �ʵ忡 ������ �ִ� ��� ���� ���� �Լ�
	void SkillShoot();		// ���� ��ų ���
};

