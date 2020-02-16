#pragma once

#include "CMonster.h"

#include <vector>
using namespace std;

class CMonster_Mgr
{
public:
	vector<Image*> m_ImgList;		// ���� �̹��� ����Ʈ
	vector<CMonster*> m_MonList;	// <--- �޸� Ǯ ���

	RECT m_cRT;						// ���� ����
	int m_SpawnLim = 6;				// �ʵ忡 �����ϴ� ���� �� ���� ����

public:
	CMonster_Mgr();
	~CMonster_Mgr();

public:
	void MonMgr_Init(HWND a_hWnd);
	void MonMgr_Update(float a_DeltaTime, HWND a_hWnd, class CHero& a_Hero);
	void MonMgr_Render(HDC a_hDC);
	void MonMgr_Destroy();

	void SpawnMonster(float a_DeltaTime, HWND a_hWnd);
};

extern CMonster_Mgr g_Mon_Mgr;
