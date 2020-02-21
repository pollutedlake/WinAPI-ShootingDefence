#include "framework.h"
#include "CMonster_Mgr.h"
#include "CHero.h"
#include "GlobalValue.h"
#include "CBullet.h"

CMonster_Mgr::CMonster_Mgr()
{
}

CMonster_Mgr::~CMonster_Mgr()
{
}

void CMonster_Mgr::MonMgr_Init(HWND a_hWnd)
{
	//------ 몬스터 이미지 로딩하기
	Image* a_ImgNode = NULL;

	// aImgNode = Image::FromFile(_T("./MonsterImg/Zombi1.png"));
	// m_ImgList.push_back(a_ImgNode);
	for (int ii = 0; ii < CT_Length; ii++) {
		a_ImgNode = NULL;
		if ((CT_Type)ii == CT_Nanami) {
			a_ImgNode = Image::FromFile(_T("./Nanami/front_Idle/n001.png"));
		}
		else if ((CT_Type)ii == CT_Zombie4) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi4.png"));
		}
		else if ((CT_Type)ii == CT_Zombie1) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi1.png"));
		}
		else if ((CT_Type)ii == CT_Zombie2) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi2.png"));
		}
		else if ((CT_Type)ii == CT_Zombie6) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi6.png"));
		}
		else if ((CT_Type)ii == CT_Zombie3) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi3.png"));
		}
		else if ((CT_Type)ii == CT_Boss) {
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Front/Megapack III Void Gargoyle.png"));
		}
		else {		// if ((CT_Type)ii == CT_Zombie3)
			a_ImgNode = Image::FromFile(_T("./MonsterImg/Zombi8.png"));
		}
		m_ImgList.push_back(a_ImgNode);
	}
	//------ 몬스터 이미지 로딩하기

	//------ 몬스터 메모리풀로 미리 만들어 놓기
	CMonster* a_Node = NULL;
	for (int aii = 0; aii < 20; aii++) {
		a_Node = new CMonster();
		a_Node->Init_Unit();
		m_MonList.push_back(a_Node);
	}
	//------ 몬스터 메모리풀로 미리 만들어 놓기

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));		// brsh 추가, pen과 같은 방식으로
}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, HWND a_hWnd, CHero& a_Hero)
{
	//------ 주기적인 Monster Spawn
	SpawnMonster(a_DeltaTime, a_hWnd);
	//------ 주기적인 Monster Spawn

	//------ Monster AI
	// 몬스터끼리 겹치지 않게 하기 관련 변수 ...
	static Vector2D a_CalcVec;
	static float a_CalcSDist;
	static float a_CalcMargin = 0.0f;
	static float a_RadiusHap;
	static Vector2D a_CalcMovePos;
	static Vector2D a_CalcSNormal;
	static float a_CalcShiftLen = 0.0f;
	// 몬스터끼리 겹치지 않게 하기 관련 변수 ...

	for (int ii = 0; ii < m_MonList.size(); ii++) {
		if (m_MonList[ii]->m_isActive == false) {
			continue;
		}

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);

		// 몬스터 끼리 겹치지 않게 하기...
		for (int xx = 0; xx < m_MonList.size(); xx++) {
			if (m_MonList[ii] == m_MonList[xx]) {
				continue;
			}

			if (m_MonList[xx]->m_isActive == false) {
				continue;
			}

			a_CalcVec = m_MonList[ii]->m_CurPos - m_MonList[xx]->m_CurPos;
			a_CalcSDist = a_CalcVec.Magnitude();
			a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + m_MonList[xx]->m_HalfColl + 4;	// (내 반경 + 적 반경) 변수 재활용
			a_CalcMovePos = m_MonList[ii]->m_CurPos;
			if (a_CalcSDist < a_RadiusHap) {		// 겹친 상태
				a_CalcMargin = a_RadiusHap - a_CalcSDist;
				a_CalcSNormal = a_CalcVec;		// 밀려야할 방향
				a_CalcSNormal.Normalize();
				a_CalcShiftLen = a_CalcMargin;
				if (a_RadiusHap < a_CalcShiftLen) {		// 안전장치 시간간격도 반지름보다 커지면 안된다.
					a_CalcShiftLen = a_RadiusHap;
				}

				a_CalcMovePos = a_CalcMovePos + (a_CalcSNormal * a_CalcShiftLen);
			}	// if (a_CalcSDist < a_RadiusHap)
			m_MonList[ii]->m_CurPos = a_CalcMovePos;
		}
		// 몬스터 끼리 겹치지 않게 하기...

		//------ 주인공과의 충돌처리
		a_CalcVec = m_MonList[ii]->m_CurPos - a_Hero.m_CurPos;
		a_CalcSDist = a_CalcVec.Magnitude();
		a_RadiusHap = m_MonList[ii]->m_HalfColl + 4 + a_Hero.m_HalfColl + 4;	// (내 반경 + 적 반경) 변수 재활용
		a_CalcMovePos = m_MonList[ii]->m_CurPos;
		if (a_CalcSDist < a_RadiusHap) {
			a_CalcMargin = a_RadiusHap - a_CalcSDist;
			a_CalcSNormal = a_CalcVec;		// 밀려야할 방향
			a_CalcSNormal.Normalize();
			a_CalcShiftLen = a_CalcMargin;
			if (a_RadiusHap < a_CalcShiftLen) {		// 안전장치 시간간격도 반지름보다 커지면 안된다.
				a_CalcShiftLen = a_RadiusHap;
			}

			a_CalcMovePos = a_CalcMovePos + (a_CalcSNormal * a_CalcShiftLen);
		}	// if (a_CalcSDist < a_RadiusHap)

		m_MonList[ii]->m_CurPos = a_CalcMovePos;
		//------ 주인공과의 충돌처리
	}	// for (int ii = 0; ii < m_MonList.size(); ii++)
	//------ Monster AI
}

void CMonster_Mgr::MonMgr_Render(HDC a_hDC)
{
	//------ 몬스터 이미지 그리기...
	for (int ii = 0; ii < m_MonList.size(); ii++) {
		if (m_MonList[ii]->m_isActive == false) {
			continue;
		}

		m_MonList[ii]->Render_Unit(a_hDC, m_R_brsh);
	}
	//------ 몬스터 이미지 그리기...
}

void CMonster_Mgr::MonMgr_Destroy()
{
	//------ 몬스터 이미지 제거하기
	for (int aii = 0; aii < m_ImgList.size(); aii++) {
		if (m_ImgList[aii] != NULL) {
			delete m_ImgList[aii];
			m_ImgList[aii] = NULL;
		}
	}
	m_ImgList.clear();
	//------ 몬스터 이미지 제거하기

	// 몬스터 메모리풀 제거하기...
	for (int aii = 0; aii < m_MonList.size(); aii++) {
		if (m_MonList[aii] != NULL) {
			m_MonList[aii]->Destroy_Unit();

			delete m_MonList[aii];
			m_MonList[aii] = NULL;
		}
	}
	m_MonList.clear();
	// 몬스터 메모리풀 제거하기...

	if (m_R_brsh != NULL) {
		DeleteObject(m_R_brsh);		// brush object 제거
		m_R_brsh = NULL;
	}
}

void CMonster_Mgr::SpawnMonster(float a_DeltaTime, HWND a_hWnd)
{
	//--- 몬스터 Active 감시 및 마리수 카운트
	static int g_MonCount = 0;
	g_MonCount = 0;
	for (int ii = 0; ii < m_MonList.size(); ii++) {
		if (m_MonList[ii]->m_isActive == true) {
			g_MonCount++;
		}
	}
	//--- 몬스터 Active 감시 및 마리수 카운트

	//------ 주기적인 Monster Spawn	<--- 몬스터 랜덤 생성
	static float a_SpawnTime = 0.0f;
	a_SpawnTime = a_SpawnTime - a_DeltaTime;
	if (a_SpawnTime < 0.0f) {
		m_SpawnLim = 6 + (g_DiffLevel - 2);
		if (m_SpawnLim < 6) {
			m_SpawnLim = 6;
		}

		if (10 < m_SpawnLim) {
			m_SpawnLim = 10;
		}

		for (int ii = 0; ii < m_MonList.size(); ii++) {
			if (m_SpawnLim <= g_MonCount) {
				break;
			}

			if (m_MonList[ii]->m_isActive == false) {
				//------ Random 하게 스폰 좌표 생성하는 부분
				// 세로 - [0] X축 -150.0f ~ -50.0f Y축 -150 ~ (float)m_cRT.bottom + 150.0f
				//        [1] X축 -50.0f ~ (int)m_cRT.right + 50.0f Y축 -150.0f ~ -50.0f
				// 세로 - [2] X축 (int)m_cRT.right + 50.0f ~ (int)m_cRT.right + 150.0f Y축 -150.0f ~ (float)m_cRT.bottom + 150.0f
				//        [3] X축 -50.0f ~ (int)m_cRT.right + 50.0f Y축 (float)m_cRT.bottom + 50.0f ~ (float)m_cRT.bottom + 150.0f
				// 양옆 <--- 위 아래 4곳중 한곳 랜덤 그중에서 랜덤으로 걸리게 하는 방법도 있다.

				static bool a_TicToc = true;
				// 한번은 x축으로
				// 한번은 y축으로

				GetClientRect(a_hWnd, &m_cRT);		// 클라이언트 화면의 크기를 받는다.

				float a_XX = 0.0f;
				float a_YY = 0.0f;
				if (a_TicToc == true) {
					a_XX = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_YLenVal = (int)m_cRT.bottom + 100;

					if (a_XX < 0.0f) {
						a_XX = a_XX - a_PushVal;
					}
					else {
						a_XX = a_XX + (float)m_cRT.right + a_PushVal;
					}

					a_YY = (float)((rand() % a_YLenVal) - (100 / 2));

					a_TicToc = false;
				}
				else {
					a_YY = (float)((rand() % 200) - 100);
					float a_PushVal = 50.0f;
					int a_XLenVal = (int)m_cRT.right + 100;

					if (a_YY < 0.0f) {
						a_YY = a_YY - a_PushVal;
					}
					else {
						a_YY = a_YY + (float)m_cRT.bottom + a_PushVal;
					}

					a_XX = (float)((rand() % a_XLenVal) - (100 / 2));

					a_TicToc = true;
				}
				//------ Random 하게 스폰 좌표 생성하는 부분

				m_MonList[ii]->m_CharType = GetSpMonType();
				m_MonList[ii]->Spawn(a_XX, a_YY);
				if (CT_None < m_MonList[ii]->m_CharType && m_MonList[ii]->m_CharType < CT_Length) {
					m_MonList[ii]->m_SocketImg = g_Mon_Mgr.m_ImgList[m_MonList[ii]->m_CharType];
					m_MonList[ii]->LoadUnitSize();
				}

				break;
			}	// if (m_MonList[ii]->m_isActive == false)
		}	// for (int ii = 0; ii < m_MonList.size(); ii++)

		a_SpawnTime = GetSpTimeLevel();
	}
	//------ 주기적인 Monster Spawn
}

void CMonster_Mgr::TakeDamage_MonMgr(CBullet* a_RefBullet)
{
	if (a_RefBullet == NULL) {
		return;
	}

	float a_Damage = 10.0f;
	if (a_RefBullet->m_BL_Type == BT_Skill1) {
		a_Damage = a_Damage * 20.0f;
	}
	else {
		a_Damage = 10.0f;
	}

	static Vector2D a_CurV;
	static Vector2D a_CalcBVec;

	//------ 총알이 몬스터에 맞았으면 제거해 준다. 몬스터 제거 총알 제거
	for (int ii = 0; ii < m_MonList.size(); ii++) {
		if (m_MonList[ii]->m_isActive == false) {
			continue;
		}

		a_CalcBVec = m_MonList[ii]->m_CurPos - a_RefBullet->m_CurPos;
		if (a_CalcBVec.Magnitude() < (m_MonList[ii]->m_HalfColl + a_RefBullet->m_HalfColl)) {		// 몬스터의 반지름 10 + 총알의 충돌반경
			m_MonList[ii]->TakeDamage(a_Damage);

			a_RefBullet->m_BLActive = false;		// 총알 제거
			break;
		}
	}
	//------ 총알이 몬스터에 맞았으면 제거해 준다. 몬스터 제거 총알 제거
}

void CMonster_Mgr::ReSrcClear()
{
	for (int ii = 0; ii < m_MonList.size(); ii++) {
		m_MonList[ii]->m_isActive = false;
	}
}

CT_Type CMonster_Mgr::GetSpMonType()
{
	CT_Type a_SpType = CT_Zombie1;

	if (g_DiffLevel <= 1) {
		a_SpType = CT_Zombie4;
	}
	else if (g_DiffLevel == 2) {
		a_SpType = CT_Zombie1;
	}
	else if (g_DiffLevel == 3) {
		a_SpType = CT_Zombie2;
	}
	else if (g_DiffLevel == 4) {
		a_SpType = CT_Zombie6;
	}
	else if (g_DiffLevel == 5 || g_DiffLevel == 6) {
		a_SpType = CT_Zombie3;
	}
	else {
		a_SpType = CT_Zombie8;
	}

	return a_SpType;
}

float CMonster_Mgr::GetSpTimeLevel()
{
	float a_SpTime = 2.0f;

	if (g_DiffLevel <= 1) {
		a_SpTime = (float)(rand() % 3 + 2);		// 다음 스폰 시간 랜덤
	}
	else if (g_DiffLevel == 2) {
		a_SpTime = (float)(rand() % 3 + 1);		// 다음 스폰 시간 랜덤
	}
	else if (g_DiffLevel == 3) {
		a_SpTime = (float)(rand() % 2 + 1);		// 다음 스폰 시간 랜덤
	}
	else if (g_DiffLevel == 4) {
		a_SpTime = 1.0f;		// 다음 스폰 시간 랜덤
	}
	else if (g_DiffLevel == 5) {
		a_SpTime = 0.5f;		// 다음 스폰 시간 랜덤
	}
	else {
		a_SpTime = 0.3f;		// 다음 스폰 시간 랜덤
	}

	return a_SpTime;
}

CMonster_Mgr g_Mon_Mgr;
