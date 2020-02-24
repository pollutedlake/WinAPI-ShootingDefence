#include "framework.h"
#include "CBossMon.h"
#include "GlobalValue.h"

#include "CBullet.h"
#include "CBullet_Mgr.h"
#include "CHero.h"

CBossMon::CBossMon()
{
	m_CharType = CT_Boss;

	m_isActive = false;
	IsAppearState = false;
}

CBossMon::~CBossMon()
{
}

void CBossMon::Init_Unit(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));
}

void CBossMon::Update_Unit(float a_DeltaTime)
{
	static RECT a_RT;
	GetClientRect(m_hWnd, &a_RT);		// Main DC�� ���� ���� ����� ������ �Լ�
	static Vector2D a_CalcVec;

	//------ Boss AI
	if (IsAppearState == true) {		// ���� ���� �������� ��Ÿ���� �÷��׺��� On ����
		// ������ �ѷ��� ������ �ִ� �ڽ��� ȭ�� �ȿ� ������ ���� ����� �Ǵ��� ������,
		// Spawn �� Target �������� �̵�
		static double a_CalcStep;
		static Vector2D a_CalcEndVec;

		// ������ ���⿡ �ð� ���� ���ؼ� ���ݾ� �̵��ϰ� �Ѵ�.
		a_CalcStep = a_DeltaTime * m_Speed;		// �̹��� �Ѱ��� ���� (����)
		a_CalcEndVec = m_TargetPos - m_CurPos;
		if (a_CalcEndVec.Magnitude() <= a_CalcStep) {		// ��ǥ�������� �Ÿ����� ������ ũ�ų� ������ �������� ����.
			IsAppearState = false;
			m_SkillCount = 0;	// �ʱ�ȭ
			m_SkillTime = (float)((rand() % 6) + 5);
		}
		else {
			m_DirVec = a_CalcEndVec;
			m_DirVec.Normalize();
			m_CurPos = m_CurPos + (m_DirVec * a_CalcStep);

			a_CalcVec = m_TargetPos - m_CurPos;
		}

		if (BossLimitMove(a_RT) == true) {		// �̰͵� ���� �Ϸ�� ����.
			IsAppearState = false;
			m_SkillCount = 0;
			m_SkillTime = (float)((rand() % 6) + 5);
		}
	}	// if (IsAppearState == true)
	else {
		// 8�� �Ŀ� �ߵ� �ñر� Ÿ��
		m_SkillTime = m_SkillTime - a_DeltaTime;
		if (m_SkillTime <= 0) {
			if (-2.5f < m_SkillTime && m_SkillTime <= -2.0f) {
				if (m_SkillCount == 0) {
					SkillShoot();
					m_SkillCount = 1;
				}
			}
			else if (-3.0f < m_SkillTime) {
				if (m_SkillCount == 1) {
					SkillShoot();
					m_SkillCount = 2;
				}
			}
			else if (-3.5f < m_SkillTime) {
				if (m_SkillCount == 2) {
					SkillShoot();
					m_SkillCount = 3;
				}
			}
			else if (-4.0f < m_SkillTime) {
				if (m_SkillCount == 3) {
					SkillShoot();
					m_SkillCount = 4;
				}
			}
			else if (-5.0f < m_SkillTime) {
				if (m_SkillCount == 4) {
					SkillShoot();
					m_SkillCount = 5;
				}
			}
			else if (-6.5f < m_SkillTime) {
				m_SkillCount = 0;
				m_SkillTime = (float)((rand() % 6) + 5);
			}
		}
		else {		// �Ϲ� ����
			// ���ΰ��� ���Ͽ� �Ѿ˹߻�
			//------ �Ѿ� �߻� ������Ʈ
			m_BLCycle = m_BLCycle + a_DeltaTime;
			if (m_AttackSpeed < m_BLCycle) {
				Vector2D a_CurV;
				a_CurV.x = m_CurPos.x;
				a_CurV.y = m_CurPos.y - 50.0f;

				g_Bullet_Mgr.SpawnBullet(a_CurV, g_Hero.m_CurPos, CT_Monster, BT_Normal);

				m_BLCycle = 0.0f;
			}
			//------ �Ѿ� �߻� ������Ʈ
		}	// �Ϲ� ����
	}	// ���� ������ ���� ��Ȳ����...

	//------ �ִϸ��̼� ������ ��� �κ�
	//if (0.0f < a_CalcVec.x) {
	//	ChangeState(Right_Walk);		// ���� ���������� �־�� �Ѵ�.
	//}
	//else {
	//	ChangeState(Left_Walk);
	//}
	//CUnit::Update_Unit(a_DeltaTime);	// �θ��� Update_Unit()�Լ� ȣ��
	//------ �ִϸ��̼� ������ ��� �κ�
	//------ Boss AI

	//------ ���ΰ����� �浹ó��
	static float a_CalcSDist;
	static float a_CalcMargin = 0.0f;
	static float a_RadiusHap;
	static Vector2D a_CalcMovePos;
	static Vector2D a_CalcSNormal;
	static float a_CalcShifLen = 0.0f;
	a_CalcVec = g_Hero.m_CurPos - m_CurPos;
	a_CalcSDist = a_CalcVec.Magnitude();
	a_RadiusHap = m_HalfColl + 4 + g_Hero.m_HalfColl + 4;		// (�� �ݰ� + �� �ݰ�) ���� ��Ȱ��

	a_CalcMovePos = g_Hero.m_CurPos;

	if (a_CalcSDist < a_RadiusHap) {
		a_CalcMargin = a_RadiusHap - a_CalcSDist;
		a_CalcSNormal = a_CalcVec;		// �з����� ����
		a_CalcSNormal.Normalize();

		a_CalcShifLen = a_CalcMargin;
		if (a_RadiusHap < a_CalcShifLen) {		// ������ġ �ð����ݵ� ���������� Ŀ���� �ȵȴ�.
			a_CalcShifLen = a_RadiusHap;
		}

		a_CalcMovePos = a_CalcMovePos + (a_CalcSNormal * a_CalcShifLen);
	}	// if (a_CalcSDist < a_RadiusHap)
	
	g_Hero.m_CurPos = a_CalcMovePos;
	//------ ���ΰ����� �浹ó��
}

void CBossMon::Render_Unit(HDC a_hDC)
{
	if (m_SocketImg == NULL) {
		return;
	}

	//------ HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, m_R_brsh);
	static float a_CalcMXX = 0.0f;
	static float a_CalcMYY = (int)(m_HalfHeight * 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CalcMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CalcMYY = (int)(m_HalfHeight * 0.97f);

	Rectangle(a_hDC, m_CurPos.x - a_CalcMXX, m_CurPos.y - a_CalcMYY, m_CurPos.x - a_CalcMXX + a_CurHpSize, m_CurPos.y - (a_CalcMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);		// ���� �귯���� ��ü
	//------ HP Bar Render

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - (int)(m_HalfHeight * 1.2f), (float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CBossMon::Destroy_Unit()
{
	if (m_R_brsh != NULL) {
		DeleteObject(m_R_brsh);
		m_R_brsh = NULL;
	}
}

void CBossMon::Spawn(float a_XX, float a_YY)
{
}

bool CBossMon::BossLimitMove(RECT& a_RT)
{
	return false;
}

void CBossMon::ReSrcClear()
{
}

void CBossMon::SkillShoot()
{
}