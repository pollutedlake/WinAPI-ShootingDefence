#pragma once

//------ GDI+ Image 사용을 위한 헤더 추가
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image 사용을 위한 헤더 추가

class CUI_Manager
{
	float m_DeltaTime = 0.0f;

	Image* m_GUIBack = NULL;
	Image* m_HP_Icon = NULL;

	TCHAR m_StrBuff[128];
	HFONT m_OldFont;
	HFONT hFont_100 = NULL;
	HFONT hFont_50 = NULL;
	HFONT m_Font_26Godic = NULL;

	HPEN h_Pen;
	HPEN h_OldPen;
	HBRUSH h_Brush;
	HBRUSH h_OldBrush;

public:
	CUI_Manager();
	~CUI_Manager();

public:
	void UIMgr_Init();
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)() = NULL, void(*ReSetGameFunc)() = NULL);		// 게임의 연산 담당 부분
	void UIMgr_Render(HDC a_MainDC, RECT& a_RT);		// 게임의 렌데링 부분
	void UIMgr_Destroy();							// 종료 처리 부분

	void UserInfoPanel(HDC a_MainDC, Graphics& graphics, RECT& a_RT);
};

extern CUI_Manager g_GUI_Mgr;

