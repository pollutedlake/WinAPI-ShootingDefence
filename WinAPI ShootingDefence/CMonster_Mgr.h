#pragma once

#include "CMonster.h"
#include "CBossMon.h"

#include <vector>
using namespace std;

class CMonster_Mgr
{
public:
	vector<Image*> m_ImgList;		// ���� �̹��� ����Ʈ
	vector<CMonster*> m_MonList;	// <--- �޸� Ǯ ���
	vector<CBossMon*> m_BossList;	// <--- ���� ���� ����Ʈ

	RECT m_cRT;						// ���� ����
	int m_SpawnLim = 6;				// �ʵ忡 �����ϴ� ���� �� ���� ����

	float m_BossSpawnTm = 3.0f;
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

	void ReSrcClear();		// ���带 �Ѿ �� �ʵ忡 ������ �ִ� ��� ���� ���� �Լ�

	CT_Type GetSpMonType();	// ���̵��� ���� ������ ���� ������ ������ �ִ� �Լ�
	float GetSpTimeLevel();	// ���̵��� ���� ���� ���� �ֱ⸦ ������ �ִ� �Լ�
};

extern CMonster_Mgr g_Mon_Mgr;

