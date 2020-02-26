#include "framework.h"
#include "CBullet.h"

HBRUSH CBullet::m_R_brsh = NULL;
HBRUSH CBullet::m_G_brsh = NULL;

CBullet::CBullet()
{
	if (m_R_brsh == NULL) {
		m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));
	}

	if (m_G_brsh == NULL) {
		m_G_brsh = CreateSolidBrush(RGB(70, 70, 70));
	}
	
	m_BLActive = false;
	m_BL_Type = BT_Normal;		// 기본은 일반 총알
	m_UC_Type = CT_Hero;

	m_LifeTime = 4.0f;
	m_MoveSpeed = 800.0f;		// 800픽셀 / 1초

	m_HalfColl = 20.0f;			// 충돌반경
}

CBullet::~CBullet()
{
	if (m_R_brsh != NULL) {
		DeleteObject(m_R_brsh);
		m_R_brsh = NULL;
	}

	if (m_G_brsh != NULL) {
		DeleteObject(m_G_brsh);
		m_G_brsh = NULL;
	}
}

bool CBullet::BulletUpdate(float a_DeltaTime)
{
	m_LifeTime = m_LifeTime - a_DeltaTime;
	if (m_LifeTime < 0.0f) {
		m_BLActive = false;
		return false;		// 일정 시간뒤에 제거해 준다.
	}

	m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_MoveSpeed));

	return true;
}

void CBullet::BulletRender(HDC a_hDC)
{
	if (m_BL_Type == BT_Skill1) {
		if (m_R_brsh != NULL) {
			a_R_Old_brsh = (HBRUSH)SelectObject(a_hDC, m_R_brsh);

			Ellipse(a_hDC, (int)(m_CurPos.x - 8.0f), (int)(m_CurPos.y - 8.0f), (int)(m_CurPos.x + 8.0f), (int)(m_CurPos.y + 8.0f));

			SelectObject(a_hDC, a_R_Old_brsh);		// 기존 브러쉬로 교체
		}
	}
	else {		// 일반 타입의 총알
		if (m_UC_Type == CT_Monster) {		// 스킬 타입의 총알
			if (m_G_brsh == NULL) {
				return;
			}

			a_R_Old_brsh = SelectObject(a_hDC, m_G_brsh);

			Ellipse(a_hDC, (int)(m_CurPos.x - 8.0f), (int)(m_CurPos.y - 8.0f), (int)(m_CurPos.x + 8.0f), (int)(m_CurPos.y + 8.0f));

			SelectObject(a_hDC, a_R_Old_brsh);		// 기존 브러쉬로 교체
		}
		else {
			Ellipse(a_hDC, (int)(m_CurPos.x - 8.0f), (int)(m_CurPos.y - 8.0f), (int)(m_CurPos.x + 8.0f), (int)(m_CurPos.y + 8.0f));
		}
	}
}
