#pragma once

#include "Vector2D.h"
#include "CBullet.h"

#include <vector>
using namespace std;

class CBullet_Mgr
{
private:
	vector<CBullet*> m_BullList;		// <--- 총알 풀 방식

	HBRUSH m_h_brsh = NULL;
	HGDIOBJ m_h_Old_brsh = NULL;
	HPEN m_h_pen = NULL;				// 선종류(실선), 두께(1), RGB색
	HGDIOBJ m_h_OldPen = NULL;

public:
	CBullet_Mgr();
	~CBullet_Mgr();

public:
	void BLMgr_Init();
	void BLMgr_Update(float a_DeltaTime, HWND a_hWnd);
	void BLMgr_Render(HDC a_hDC);
	void BLMgr_Destroy();

	void SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV);
};

extern CBullet_Mgr g_Bullet_Mgr;

