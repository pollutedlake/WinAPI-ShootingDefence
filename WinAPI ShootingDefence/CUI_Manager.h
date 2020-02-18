#pragma once

//------ GDI+ Image ����� ���� ��� �߰�
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image ����� ���� ��� �߰�

class CUI_Manager
{
	Image* m_GUIBack = NULL;
	Image* m_HP_Icon = NULL;

	TCHAR m_StrBuff[128];
	HFONT m_OldFont;
	HFONT m_Font_26Godic = NULL;

public:
	CUI_Manager();
	~CUI_Manager();

public:
	void UIMgr_Init();
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)() = NULL, void(*ReSetGameFunc)() = NULL);		// ������ ���� ��� �κ�
	void UIMgr_Render(HDC a_MainDC, RECT& a_RT);		// ������ ������ �κ�
	void UIMgr_Destroy();							// ���� ó�� �κ�

	void UserInfoPanel(HDC a_MainDC, Graphics& graphics, RECT& a_RT);
};

extern CUI_Manager g_GUI_Mgr;

