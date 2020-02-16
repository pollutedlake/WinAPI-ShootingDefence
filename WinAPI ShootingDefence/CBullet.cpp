#include "framework.h"
#include "CBullet.h"

CBullet::CBullet()
{
	m_BLActive = false;

	m_LifeTime = 4.0f;
	m_MoveSpeed = 800.0f;		// 800�ȼ� / 1��

	m_HalfColl = 20.0f;			// �浹�ݰ�
}

CBullet::~CBullet()
{
}

bool CBullet::BulletUpdate(float a_DeltaTime)
{
	m_LifeTime = m_LifeTime - a_DeltaTime;
	if (m_LifeTime < 0.0f) {
		m_BLActive = false;
		return false;		// ���� �ð��ڿ� ������ �ش�.
	}

	m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_MoveSpeed));

	return true;
}

void CBullet::BulletRender(HDC a_hDC)
{
	Ellipse(a_hDC, (int)(m_CurPos.x - 8.0f), (int)(m_CurPos.y - 8.0f), (int)(m_CurPos.x + 8.0f), (int)(m_CurPos.y + 8.0f));
}
