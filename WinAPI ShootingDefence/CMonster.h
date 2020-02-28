#pragma once

#include "Vector2D.h"
#include "CUnit.h"

class CMonster : public CUnit
{
public:
	bool m_isActive;
	float m_MaxHP = 100.0f;
	float m_CurHP = 100.0f;

	//--- ���� ��ǥ ���� ������...
	Vector2D m_CurPos;
	float m_Speed = 150.0f;
	Vector2D m_DirVec;
	float m_HalfColl = 17;		// ������ �浹 �ݰ�
	//--- ���� ��ǥ ���� ������...

public:
	CMonster();
	~CMonster();

public:
	void Init_Unit();
	void Update_Unit(float a_DeltaTime, class CHero& a_Hero);
	void Render_Unit(HDC a_hDC, HBRUSH& a_R_brsh);
	void Destroy_Unit();

	void Spawn(float a_XX, float a_YY);
	void TakeDamage(float a_Value = 10.0f);
};

