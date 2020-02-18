#include "framework.h"
#include "CMyMain.h"
#include "CBackGround.h"
#include "CHero.h"
#include "GlobalValue.h"
#include "CBullet_Mgr.h"
#include "CMonster_Mgr.h"
#include "CItem_Mgr.h"
#include "CUI_Manager.h"

#include <mmsystem.h>					// timeGetTime() �Լ� ����� ���Ͽ� ...
#include <time.h>						// <--- �������� ��� ���Ͽ�...
#pragma comment(lib, "winmm.lib")		// timeGetTime() �Լ� ����� ���Ͽ�...

CMyMain::CMyMain()
{
}

CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HWND hWnd)
{
	m_hWnd = hWnd;
	GetClientRect(hWnd, &m_Rect);		// Ŭ���̾�Ʈ ȭ���� ũ�⸦ �޴´�.

	srand((unsigned)time(NULL));		// rand �ʱ�ȭ
	// DeltaTime ��� ���� ���
	m_LastTime = timeGetTime();			// ���� �ð� ��������

	//------ GDI+ �ʱ�ȭ (������Ʈ �������ڸ��� �ѹ��� ���ָ� �ȴ�,)
	GdiplusStartupInput  gdiplusStartInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartInput, NULL);
	//------ GDI+ �ʱ�ȭ (������Ʈ �������ڸ��� �ѹ��� ���ָ� �ȴ�,)

	//------ �ĸ� BackDC ����
	HDC a_hdc = GetDC(hWnd);		// ���� DC ��������...
	m_hBackDC = CreateCompatibleDC(a_hdc);		// ���� DC�� �ֵ��� ���纻 DC�� �ϳ� �����.
	m_hBackBitmap = CreateCompatibleBitmap(a_hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));	// BackDC�� �ٿ��� Bitmap(�̹���)�� �ϳ� ����� �ش�.
	SelectObject(m_hBackDC, m_hBackBitmap);		// BackDC�� Bitmap(�̹���)�� �ٿ��ش�.
	ReleaseDC(hWnd, a_hdc);
	//------ �ĸ� BackDC ����

	//------ GUI �ʱ�ȭ
	g_GUI_Mgr.UIMgr_Init();
	//------ GUI �ʱ�ȭ

	//------ ��׶��� �ʱ�ȭ
	g_BGround.BG_Init(hWnd);
	//------ ��׶��� �ʱ�ȭ

	//------ ���ΰ� �ʱ�ȭ
	g_Hero.Init_Unit(hWnd);
	//------ ���ΰ� �ʱ�ȭ

	//------ �Ѿ� �Ŵ��� �ʱ�ȭ
	g_Bullet_Mgr.BLMgr_Init();
	//------ �Ѿ� �Ŵ��� �ʱ�ȭ

	//------ ���� �Ŵ��� �ʱ�ȭ
	g_Mon_Mgr.MonMgr_Init(hWnd);
	//------ ���� �Ŵ��� �ʱ�ȭ

	//------ ������ �Ŵ��� �ʱ�ȭ
	g_ItemMgr.ItemMgr_Init();
	//------ ������ �Ŵ��� �ʱ�ȭ
}

void CMyMain::MainUpdate(HWND hWnd)
{
	//------ DeltaTime ������ ���
	timeBeginPeriod(1);
	m_CurTime = timeGetTime();
	m_DeltaTime = (m_CurTime - m_LastTime) * 0.001f;
	m_LastTime = m_CurTime;
	timeEndPeriod(1);
	//------ DeltaTime ������ ���

	if (m_hBackDC == NULL) {
		return;
	}

	GetClientRect(hWnd, &m_Rect);

	//------ ��׶��� ������Ʈ
	// g_BGround.BG_Update();
	//------ ��׶��� ������Ʈ

	//------ ���ΰ� ������Ʈ
	g_Hero.Update_Unit(m_DeltaTime, m_Rect);
	//------ ���ΰ� ������Ʈ

	//------ ���� �Ŵ��� ������Ʈ
	g_Mon_Mgr.MonMgr_Update(m_DeltaTime, hWnd, g_Hero);
	//------ ���� �Ŵ��� ������Ʈ

	//------ �Ѿ� �Ŵ��� ������Ʈ
	g_Bullet_Mgr.BLMgr_Update(m_DeltaTime, m_hWnd, &g_Mon_Mgr);
	//------ �Ѿ� �Ŵ��� ������Ʈ

	//------ ������ �Ŵ��� ������Ʈ
	g_ItemMgr.ItemMgr_Update(m_DeltaTime);
	//------ ������ �Ŵ��� ������Ʈ

	//------ GUI ������Ʈ
	g_GUI_Mgr.UIMgr_Update(hWnd, m_DeltaTime, NULL, NULL);
	//------ GUI ������Ʈ
}

void CMyMain::MainRender(HWND hWnd)
{
	if (m_hBackDC == NULL) {
		return;
	}

	//------ ��׶��� ����
	g_BGround.BG_Render(m_hBackDC, m_Rect);
	//------ ��׶��� ����

	//------ ������ ����
	g_ItemMgr.ItemMgr_Render(m_hBackDC);
	//------ ������ ����

	//------ ���� �̹��� ����...
	g_Mon_Mgr.MonMgr_Render(m_hBackDC);		// ������ �� �Ѿ��� ��� ���� �������Բ� ���� ������
	//------ ���� �̹��� ����...

	//------ �Ѿ� ����
	g_Bullet_Mgr.BLMgr_Render(m_hBackDC);
	//------ �Ѿ� ����

	//------ ���ΰ� ����
	g_Hero.Render_Unit(m_hBackDC);
	//------ ���ΰ� ����

	//------ GUI ������
	g_GUI_Mgr.UIMgr_Render(m_hBackDC, m_Rect);
	//------ GUI ������

	//------ ȭ����ȯ
	static HDC hdc;
	hdc = GetDC(hWnd);
	BitBlt(hdc, 0, 0, m_Rect.right, m_Rect.bottom, m_hBackDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
	//------ ȭ����ȯ
}

void CMyMain::MainDestroy()
{
	//------ ������ ����
	g_ItemMgr.ItemMgr_Destroy();
	//------ ������ ����

	//------ ���� ����
	g_Mon_Mgr.MonMgr_Destroy();
	//------ ���� ����

	//------ �Ѿ� ����
	g_Bullet_Mgr.BLMgr_Destroy();
	//------ �Ѿ� ����

	//------ ���ΰ� ����
	g_Hero.Destroy_Unit();
	//------ ���ΰ� ����

	//------ ��׶��� ����
	g_BGround.BG_Destroy();
	//------ ��׶��� ����

	//------ GUI ����
	g_GUI_Mgr.UIMgr_Destroy();
	//------ GUI ����

	//------ �ĸ� BackDC ����
	if (m_hBackBitmap != NULL) {
		DeleteObject(m_hBackBitmap);
		m_hBackBitmap = NULL;
	}

	if (m_hBackDC != NULL) {
		DeleteDC(m_hBackDC);
		m_hBackDC = NULL;
	}
	//------ �ĸ� BackDC ����

	//------ GDI+ ���� <--- �ٸ� ��� �̹��� ���� �� �� �������� �ѹ� �ؾ� �Ѵ�.
	if (m_gdiplusToken != NULL) {
		GdiplusShutdown(m_gdiplusToken);
		m_gdiplusToken = NULL;
	}
	//------ GDI+ ���� <--- �ٸ� ��� �̹��� ���� �� �� �������� �ѹ� �ؾ� �Ѵ�.
}

CMyMain g_CMyMain;