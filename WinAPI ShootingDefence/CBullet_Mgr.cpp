#include "framework.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"

CBullet_Mgr::CBullet_Mgr()
{
}

CBullet_Mgr::~CBullet_Mgr()
{
}

void CBullet_Mgr::BLMgr_Init()
{
	//------ 총알 메모리풀로 미리 만들어 놓기
	CBullet* a_BLNode = NULL;
	for (int aii = 0; aii < 200; aii++) {
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
	}
	//------ 총알 메모리풀로 미리 만들어 놓기

	m_h_brsh = CreateSolidBrush(RGB(0, 100, 255));		// brush 추가, pen과 같은 방식으로
	m_h_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// 선종류(실선), 두께(1), RGB색
}

void CBullet_Mgr::BLMgr_Update(float a_DeltaTime, HWND a_hWnd, CMonster_Mgr* a_MonMgr)
{
	//------ 모든 총알 이동관련 업데이트 처리
	static Vector2D a_CalcBVec;
	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			continue;
		}

		m_BullList[aii]->BulletUpdate(a_DeltaTime);

		a_MonMgr->TakeDamage_MonMgr(m_BullList[aii]);
	}	// for (int aii = 0; aii < m_BullList.size(); aii++)
	//------ 모든 총알 이동관련 업데이트 처리
}

void CBullet_Mgr::BLMgr_Render(HDC a_hDC)
{
	if (m_h_pen == NULL || m_h_brsh == NULL) {
		return;
	}

	m_h_OldPen = SelectObject(a_hDC, m_h_pen);		// HGDIOBJ 모든 GDI object의 집합
	m_h_Old_brsh = SelectObject(a_hDC, m_h_brsh);

	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			continue;
		}

		m_BullList[aii]->BulletRender(a_hDC);
	}	// for (m_Biter = m_StdList.begin(); m_Biter != m_StdList.end(); m_Biter++)

	SelectObject(a_hDC, m_h_OldPen);		// 기존 펜으로 교체
	SelectObject(a_hDC, m_h_Old_brsh);		// 기존 브러쉬로 교체
}

void CBullet_Mgr::BLMgr_Destroy()
{
	// 총알 메모리풀 제거하기...
	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii] != NULL) {
			delete m_BullList[aii];
			m_BullList[aii] = NULL;
		}
	}
	m_BullList.clear();
	// 총알 메모리풀 제거하기...

	if (m_h_brsh != NULL) {
		DeleteObject(m_h_brsh);		// brush object 제거
		m_h_brsh = NULL;
	}

	if (m_h_pen != NULL) {
		DeleteObject(m_h_pen);		// GDI object 생성 개수는 운영체제에서 정해져 있음
		m_h_pen = NULL;
	}
}

void CBullet_Mgr::SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV, BulletType a_BLTP)
{
	CBullet* a_BNode = NULL;

	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			a_BNode = m_BullList[aii];
			break;
		}
	}

	if (a_BNode == NULL) {
		a_BNode = new CBullet();
		m_BullList.push_back(a_BNode);
	}

	a_BNode->m_CurPos.x = a_StartV.x;
	a_BNode->m_CurPos.y = a_StartV.y;

	a_BNode->m_DirVec = a_TargetV - a_StartV;
	a_BNode->m_DirVec.Normalize();
	a_BNode->m_CurPos = a_BNode->m_CurPos + a_BNode->m_DirVec * 20.0f;
	a_BNode->m_BLActive = true;
	a_BNode->m_LifeTime = 4.0f;
	a_BNode->m_BL_Type = a_BLTP;
}

CBullet_Mgr g_Bullet_Mgr;