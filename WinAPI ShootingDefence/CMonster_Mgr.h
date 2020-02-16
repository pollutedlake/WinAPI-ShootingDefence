#pragma once

#include "CMonster.h"

#include <vector>
using namespace std;

class CMonster_Mgr
{
public:
	vector<Image*> m_ImgList;		// 몬스터 이미지 리스트
	vector<CMonster*> m_MonList;	// <--- 메모리 풀 방식

	RECT m_cRT;						// 계산용 변수
	int m_SpawnLim = 6;				// 필드에 등장하는 몬스터 수 제어 변수

	HBRUSH m_R_brsh;
	HGDIOBJ m_R_Old_brsh;

public:
	CMonster_Mgr();
	~CMonster_Mgr();

public:
	void MonMgr_Init(HWND a_hWnd);
	void MonMgr_Update(float a_DeltaTime, HWND a_hWnd, class CHero& a_Hero);
	void MonMgr_Render(HDC a_hDC);
	void MonMgr_Destroy();

	void SpawnMonster(float a_DeltaTime, HWND a_hWnd);
	void TakeDamage_MonMgr(class CBullet* a_RefBullet = NULL);
};

extern CMonster_Mgr g_Mon_Mgr;

