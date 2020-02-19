#include "framework.h"
#include "CMonster.h"
#include "CHero.h"
#include "GlobalValue.h"
#include "CItem_Mgr.h"

CMonster::CMonster()
{
	m_CharType = CT_Zombie1;		// 캐릭터 종류가 "몬스터"인지? "나나미"인지?

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

	if (0.0f < a_Hero.m_SdOnTime) {		// 쉴드 적용중이라면
		if (a_CalcVec.Magnitude() < a_Hero.m_SdHalfSize) {
			a_DeltaTime = a_DeltaTime * 0.05f;
		}
	}

	//------ Monster AI
	if (a_Hero.m_HalfColl + m_HalfColl < a_CalcVec.Magnitude()) {		// (충돌반경의 합 < 중점의 거리) 아직 추적
		m_DirVec = a_CalcVec;
		m_DirVec.Normalize();
		m_CurPos = m_CurPos + (m_DirVec * (a_DeltaTime * m_Speed));
	}
	//------ Monster AI

	//------ 몬스터 공격 처리 부분
	static float m_AttackTick = 0.0f;
	m_AttackTick = m_AttackTick - a_DeltaTime;
	if (a_CalcVec.Magnitude() < (a_Hero.m_HalfColl + m_HalfColl + 10.0f)) {
		if (m_AttackTick < 0.0f) {		// 공격 범위 안에 들어오면 즉시 공격
			// 몬스터가 주인공 공격
			a_Hero.TakeDamage(10);

			m_AttackTick = 1.0f;
		}
	}
	//------ 몬스터 공격 처리 부분
}

void CMonster::Render_Unit(HDC a_hDC, HBRUSH& a_R_brsh)
{
	if (m_SocketImg == NULL) {
		return;
	}

	//------ HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, a_R_brsh);
	static float a_CalcMXX = 0.0f;
	static float a_CalcMYY = (int)(m_HalfHeight + 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CalcMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CalcMYY = (int)(m_HalfHeight * 0.97f);
	if (m_CharType == CT_Zombie1) {
		a_CalcMYY = (int)(m_HalfHeight * 0.83f);
	}
	else if (m_CharType == CT_Zombie2 || m_CharType == CT_Zombie4) {
		a_CalcMYY = (int)(m_HalfHeight * 0.83f);
	}

	Rectangle(a_hDC, m_CurPos.x - a_CalcMXX, m_CurPos.y - a_CalcMYY, m_CurPos.x - a_CalcMXX + a_CurHpSize, m_CurPos.y - (a_CalcMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);		// 기존 브러쉬로 교체
	//------ HP Bar Render

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

	m_ImgSizeX = m_SocketImg->GetWidth();		// 기본 이미지의 가로 사이즈
	m_ImgSizeY = m_SocketImg->GetHeight();		// 기본 이미지의 세로 사이즈

	m_HalfWidth = m_ImgSizeX / 2;				// 기본 이미지의 가로 반사이즈
	m_HalfHeight = m_ImgSizeY / 2;				// 기본 이미지의 세로 반사이즈
}

void CMonster::Spawn(float a_XX, float a_YY)
{
	m_CurPos.x = a_XX;
	m_CurPos.y = a_YY;

	m_isActive = true;

	m_CurHP = m_MaxHP;

	// SetAni_Rsc(m_CharType);
}

void CMonster::TakeDamage(float a_Value)
{
	m_CurHP = m_CurHP - a_Value;

	if (m_CurHP <= 0.0f) {		// 몬스터 사망 처리
		m_CurHP = 0.0f;
		g_Hero.m_KillCount++;

		//------ Item 스폰
		g_ItemMgr.SpawnItem(m_CurPos);
		//------ Item 스폰

		m_isActive = false;		//------ 사망 몬스터 제거
	}
}
