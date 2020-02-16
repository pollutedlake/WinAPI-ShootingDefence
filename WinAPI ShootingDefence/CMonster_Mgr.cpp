#include "framework.h"
#include "CMonster_Mgr.h"
#include "CHero.h"
#include "GlobalValue.h"

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
}

void CMonster_Mgr::MonMgr_Update(float a_DeltaTime, HWND a_hWnd, CHero& a_Hero)
{
	//------ 주기적인 Monster Spawn
	SpawnMonster(a_DeltaTime, a_hWnd);
	//------ 주기적인 Monster Spawn

	//------ Monster AI
	for (int ii = 0; ii < m_MonList.size(); ii++) {
		if (m_MonList[ii]->m_isActive == false) {
			continue;
		}

		m_MonList[ii]->Update_Unit(a_DeltaTime, a_Hero);
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

		HBRUSH a_R_brsh;
		m_MonList[ii]->Render_Unit(a_hDC, a_R_brsh);
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
}

void CMonster_Mgr::SpawnMonster(float a_DeltaTime, HWND a_hWnd)
{
}

CMonster_Mgr g_Mon_Mgr;
