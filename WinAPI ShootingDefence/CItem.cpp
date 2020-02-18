#include "framework.h"
#include "CItem.h"
#include "CHero.h"

CItem::CItem()
{
	m_IT_Type = IT_Gold;
	m_Duration = 10.0f;
	m_HalfWidth = 0.0f;
	m_HalfHeight = 0.0f;
	m_ItemImg = NULL;
}

CItem::~CItem()
{
}

bool CItem::ItemUpdate(float a_DeltaTime)
{
	m_Duration = m_Duration - a_DeltaTime;
	if (m_Duration < 0.0f) {
		return false;		// ���� �ð��ڿ� ������ �ش�.
	}

	m_CalcVec = g_Hero.m_CurPos - m_CurPos;
	if (m_CalcVec.Magnitude() < (g_Hero.m_HalfColl + m_HalfWidth)) {		// ���ΰ��� ������ + Item�� �浹�ݰ�
		if (m_IT_Type == IT_Potion) {
			g_Hero.m_CurHP = g_Hero.m_CurHP + 20.0f;
			if (g_Hero.m_MaxHP < g_Hero.m_CurHP) {
				g_Hero.m_CurHP = g_Hero.m_MaxHP;
			}
		}
		else if (m_IT_Type == IT_Gold) {
			g_Hero.m_MyMoney = g_Hero.m_MyMoney + 100;
		}
		else if (m_IT_Type == IT_Silver) {
			g_Hero.m_MyMoney = g_Hero.m_MyMoney + 50;
		}

		return false;
	}	// if (a_CalcVec.Magnitude() < (g_Hero.m_HalfColl + m_HalfWidth))

	return true;
}

void CItem::ItemRender(HDC a_hDC)
{
	if (m_ItemImg == NULL) {
		return;
	}

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_ItemImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - m_HalfHeight, (float)m_ItemImg->GetWidth(), (float)m_ItemImg->GetHeight());
}
