#pragma once
#include "Vector2D.h"

class CBullet
{
public:
	bool m_BLActive;		// �Ѿ��� ��Ƽ�� ����

	float m_LifeTime;		// �Ѿ��� ������ Ÿ��(�Ѿ��� ���ʵ��� ���ư��� �� �������� �ð�)
	Vector2D m_CurPos;		// �Ѿ��� ���� ��ġ
	Vector2D m_DirVec;		// �Ѿ��� ���ư��� ���⺤��
	float m_MoveSpeed;		// �Ѿ��� �̵� �ӵ�

	float m_HalfColl;		// �浹 �ݰ�

public:
	CBullet();
	~CBullet();

public:
	bool BulletUpdate(float a_DeltaTime);
	void BulletRender(HDC a_hDC);
};

