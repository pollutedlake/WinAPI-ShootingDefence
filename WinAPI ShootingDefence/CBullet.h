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
	bool m_BLActive;		// �Ѿ��� ��Ƽ�� ����
	BulletType m_BL_Type;	// �Ѿ��� �Ϲ� �Ѿ�����? ��ų �Ѿ�����?

	float m_LifeTime;		// �Ѿ��� ������ Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �� �������� �ð�)
	Vector2D m_CurPos;		// �Ѿ��� ���� ��ġ
	Vector2D m_DirVec;		// �Ѿ��� ���ư��� ���⺤��
	float m_MoveSpeed;		// �Ѿ��� �̵� �ӵ�

	float m_HalfColl;		// �浹 �ݰ�

	static HBRUSH m_R_brsh;
	HGDIOBJ a_R_Old_brsh;

public:
	CBullet();
	~CBullet();

public:
	bool BulletUpdate(float a_DeltaTime);
	void BulletRender(HDC a_hDC);
};

