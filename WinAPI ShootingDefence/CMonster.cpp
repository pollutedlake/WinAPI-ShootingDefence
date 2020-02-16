#include "framework.h"
#include "CMonster.h"
#include "CHero.h"
#include "GlobalValue.h"

CMonster::CMonster()
{
	m_CharType = CT_Zombie1;		// ĳ���� ������ "����"����? "������"����?

	m_isActive = false;

	m_MaxHP = 100.0f;
	m_CurHP = 100.0f;

	m_Speed = 150.0f;
	m_HalfColl = 20;
}

CMonster::~CMonster()
{
}

void CMonster::Init_Unit()
{
}

void CMonster::Update_Unit(float a_DeltaTime, CHero& a_Hero)
{
	Vector2D a_CalcVec = a_Hero.m_CurPos - m_CurPos;
	//------ Monster AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CalcVec.Magnitude()) {		// (�浹�ݰ��� �� < ������ �Ÿ�) ���� ����
		m_DirVec = a_CalcVec;
		m_DirVec.Normalize();
		m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));
	}
	//------ Monster AI
}

void CMonster::Render_Unit(HDC a_hDC, HBRUSH& a_R_brsh)
{
	if (m_SocketImg == NULL) {
		return;
	}

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - (int)(m_HalfHeight * 1.2f), (float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CMonster::Destroy_Unit()
{
}

void CMonster::LoadUnitSize()
{
	if (m_SocketImg == NULL) {
		return;
	}

	m_ImgSizeX = m_SocketImg->GetWidth();		// �⺻ �̹����� ���� ������
	m_ImgSizeY = m_SocketImg->GetHeight();		// �⺻ �̹����� ���� ������

	m_HalfWidth = m_ImgSizeX / 2;				// �⺻ �̹����� ���� �ݻ�����
	m_HalfHeight = m_ImgSizeY / 2;				// �⺻ �̹����� ���� �ݻ�����
}
