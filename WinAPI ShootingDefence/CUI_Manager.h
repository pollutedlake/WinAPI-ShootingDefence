#pragma once

#include "CButton.h"

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

	//------ Shop
public:
	bool m_ShopOnOff;

private:
	Image* m_ShopBase;
	ColorMatrix m_AlphaCM;

	HFONT m_HumanF;

	CButton m_CloseBtn;		// �ݱ� ��ư

	Image* m_ShopBG[3];
	Image* m_Image[3];
	Image* m_CoinImg[3];
	CButton m_AddBtn[3];	// Add ��ư
	//------ Shop

public:
	CUI_Manager();
	~CUI_Manager();

public:
	void UIMgr_Init();
	void UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)() = NULL, void(*ReSetGameFunc)() = NULL);		// ������ ���� ��� �κ�
	void UIMgr_Render(HDC a_MainDC, RECT& a_RT);		// ������ ������ �κ�
	void UIMgr_Destroy();							// ���� ó�� �κ�

	void UserInfoPanel(HDC a_MainDC, Graphics& graphics, RECT& a_RT);

	void StoreInit();
	void StoreRender(HDC a_MainDC, Graphics& graphics, RECT& a_RT);
	void StoreDestroy();

	void LBtnDown(HWND a_hWnd);
	void LBtnUp();
};

extern CUI_Manager g_GUI_Mgr;

