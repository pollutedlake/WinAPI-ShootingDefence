#pragma once
#include "Vector2D.h"

enum UClassType {
	CT_Unit = 0,
	CT_Hero,
	CT_Monster,
};

enum BulletType {
	BT_Normal = 0,
	BT_Skill1,
};

class CBullet
{
public:
	bool m_BLActive;		// 총알의 액티브 상태
	BulletType m_BL_Type;	// 총알이 일반 총알인지? 스킬 총알인지?

	float m_LifeTime;		// 총알의 라이프 타임(총알을 몇초동안 날아가게 할 것인지의 시간)
	Vector2D m_CurPos;		// 총알의 현재 위치
	Vector2D m_DirVec;		// 총알의 날아가는 방향벡터
	float m_MoveSpeed;		// 총알의 이동 속도

	float m_HalfColl;		// 충돌 반경

	static HBRUSH m_R_brsh;
	HGDIOBJ a_R_Old_brsh;

public:
	CBullet();
	~CBullet();

public:
	bool BulletUpdate(float a_DeltaTime);
	void BulletRender(HDC a_hDC);
};

